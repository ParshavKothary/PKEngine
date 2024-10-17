#include <Systems/PKRendering.h>
#include <EngineComponents/PKMeshComponent.h>
#include <Game/PKGameObject.h>

#include <glad/glad.h>

namespace pkengine
{

    #define BUFFER_VERT_COUNT 8000

    #pragma region Shader Definitions

	// Shaders/simple_vertex.glsl
	const char* CRenderer::VertexShaderSource = R"(
        #version 460 core
        layout(location = 0) in vec3 aPos;
        layout(location = 1) in vec3 aCol;

        out vec3 VertColor;

        uniform mat4 CameraTransform;

        void main()
        {
	        gl_Position = CameraTransform * vec4(aPos, 1.0);
	        VertColor = aCol;
        }
    )";

	// Shaders/simple_fragment.glsl
	const char* CRenderer::FragmentShaderSource = R"(
		#version 460 core
        in vec3 VertColor;
        out vec4 FragColor;

        void main()
        {
	        FragColor = vec4(VertColor, 1.0f);
        }
	)";

    #pragma endregion

    #pragma region Public Static

    CRenderer* CRenderer::Instance = nullptr;

    bool CRenderer::Init(const int WindowWidth, const int WindowHeight, const char* WindowTitle)
    {
        Instance = new CRenderer(WindowWidth, WindowHeight, WindowTitle);
        if (Instance->Window == nullptr)
        {
            delete Instance;
            return false;
        }

        return true;
    }

    void CRenderer::Exit()
    {
        if (Instance != nullptr)
        {
            delete Instance;
        }
    }

    bool CRenderer::RegisterMesh(CMeshComponent* MeshComponent)
    {
        assert(bInit());
        assert(MeshComponent != nullptr);

        if (Instance->AddMeshToBuffer(MeshComponent) == false)
        {
            std::cout << "Error registering mesh into Renderer. Buffer might be full." << std::endl;
            return false;
        }

        return true;
    }

    void CRenderer::UnregisterMesh(CMeshComponent* MeshComponent)
    {
        assert(bInit());
        assert(MeshComponent != nullptr);

        Instance->RemoveMeshFromBuffer(MeshComponent);
    }

    void CRenderer::Update(FTransform* CameraTransform)
    {
        assert(bInit());
        Instance->InternalDraw(CameraTransform);
    }

    #pragma endregion

    #pragma region Helpers

    bool CRenderer::ShaderCompileCheck(const unsigned int& ShaderObj, const GLenum Status)
    {
        int Success;
        char InfoLog[512];

        glGetProgramiv(ShaderObj, Status, &Success);
        if (Success == false)
        {
            glGetProgramInfoLog(ShaderObj, 512, NULL, InfoLog);
            std::cout << "Error compiling shaders\n" << InfoLog << std::endl;
            return false;
        }

        return true;
    }

    #pragma endregion

    CRenderer::CRenderer(const int WindowWidth, const int WindowHeight, const char* WindowTitle)
    {
        Window = nullptr;

        ShaderProgram = 0;
        VAO = 0;
        VBO = 0;

        MeshComponents = containers::list<CMeshComponent*>();

        // Init Window
        {
            glfwInit();
            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
            glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
            glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

            Window = glfwCreateWindow(WindowWidth, WindowHeight, WindowTitle, NULL, NULL);
            if (Window == NULL)
            {
                std::cout << "Failed to create GLFW window" << std::endl;
                CleanUp();
                return;
            }

            glfwMakeContextCurrent(Window);
            AspectRatio = float(WindowWidth) / float(WindowHeight);
        }

        // Init GL Function library
        {
            // Init glad (get gl functions)
            if (gladLoadGLLoader((GLADloadproc)glfwGetProcAddress) == false)
            {
                std::cout << "Failed to initialize GLAD" << std::endl;
                CleanUp();
                return;
            }
        }

        // Init Shader Program
        {
            unsigned int VertexShader;
            VertexShader = glCreateShader(GL_VERTEX_SHADER);
            glShaderSource(VertexShader, 1, &VertexShaderSource, NULL);
            glCompileShader(VertexShader);

            if (ShaderCompileCheck(VertexShader, GL_COMPILE_STATUS) == false)
            {
                CleanUp();
                return;
            }

            unsigned int FragmentShader;
            FragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
            glShaderSource(FragmentShader, 1, &FragmentShaderSource, NULL);
            glCompileShader(FragmentShader);

            if (ShaderCompileCheck(FragmentShader, GL_COMPILE_STATUS) == false)
            {
                CleanUp();
                return;
            }

            ShaderProgram = glCreateProgram();

            glAttachShader(ShaderProgram, VertexShader);
            glAttachShader(ShaderProgram, FragmentShader);
            glLinkProgram(ShaderProgram);

            if (ShaderCompileCheck(ShaderProgram, GL_LINK_STATUS) == false)
            {
                CleanUp();
                return;
            }

            glDeleteShader(VertexShader);
            glDeleteShader(FragmentShader);
            glUseProgram(ShaderProgram);
            CameraTransformLocation = glGetUniformLocation(ShaderProgram, "CameraTransform");
        }

        // Init Buffer
        {
            VertexData = containers::vector<FVertexData>(BUFFER_VERT_COUNT);

            glGenBuffers(1, &VBO);
            glGenVertexArrays(1, &VAO);

            glBindVertexArray(VAO);
            glBindBuffer(GL_ARRAY_BUFFER, VBO);
            glBufferData(GL_ARRAY_BUFFER, sizeof(FVertexData) * VertexData.size(), VertexData.data(), GL_DYNAMIC_DRAW);

            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(FVertexData), (void*)0);
            glEnableVertexAttribArray(0);

            glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(FVertexData), (void*)(sizeof(FVector3)));
            glEnableVertexAttribArray(1);

            glBindBuffer(GL_ARRAY_BUFFER, 0);
            glBindVertexArray(0);
        }
    }

    CRenderer::~CRenderer()
    {
        CleanUp();
    }

    void CRenderer::CleanUp()
    {
        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
        glDeleteProgram(ShaderProgram);
        glfwTerminate();

        Window = nullptr;
        VAO = 0;
        VBO = 0;
        ShaderProgram = 0;

        assert(MeshComponents.begin() == MeshComponents.end()); // All Meshes should have unregistered
    }

    void CRenderer::InternalDraw(FTransform* CameraTransform)
    {
        for (CMeshComponent* const& MeshComponent : MeshComponents)
        {
            TransformAndCopyMeshVertices(MeshComponent);
        }

        // set proj matrix
        {
            float width = 0.5f;
            float height = width / AspectRatio;

            FVector3 leftBottom = *CameraTransform * FVector3(-width, -height, 0.0f);
            FVector3 rightTop = *CameraTransform * FVector3(width, height, 0.0f);

            glm::mat4 proj = glm::ortho(leftBottom.GetX(), rightTop.GetX(), leftBottom.GetY(), rightTop.GetY());
            glUniformMatrix4fv(CameraTransformLocation, 1, GL_FALSE, glm::value_ptr(proj));
        }

        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(FVertexData) * VertexData.size(), VertexData.data(), GL_DYNAMIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glDrawArrays(GL_TRIANGLES, 0, NumActiveVerts);

        glfwSwapBuffers(Window);
    }

    bool CRenderer::AddMeshToBuffer(CMeshComponent* MeshComponent)
    {
        const unsigned int NewNumVerts = NumActiveVerts + CMeshComponent::NumVertices;
        if (NewNumVerts > VertexData.size())
        {
            return false;
        }

        MeshComponent->RendererIndex = NumActiveVerts;
        NumActiveVerts += CMeshComponent::NumVertices;

        MeshComponents.push_back(MeshComponent);
        
        return true;
    }
    
    void CRenderer::RemoveMeshFromBuffer(CMeshComponent* MeshComponent)
    {
        MeshComponent->RendererIndex = -1;
        NumActiveVerts -= CMeshComponent::NumVertices;

        containers::list<CMeshComponent*>::iterator CurrMesh = std::find(MeshComponents.begin(), MeshComponents.end(), MeshComponent);
        assert(CurrMesh != MeshComponents.end());
        for (++CurrMesh; CurrMesh != MeshComponents.end(); ++CurrMesh)
        {
            (*CurrMesh)->RendererIndex -= CMeshComponent::NumVertices;
        }

        MeshComponents.remove(MeshComponent);
    }

    void CRenderer::TransformAndCopyMeshVertices(CMeshComponent* MeshComponent)
    {
        assert(MeshComponent->RendererIndex >= 0);
        assert(MeshComponent->RendererIndex + CMeshComponent::NumVertices <= NumActiveVerts);

        const unsigned int StartIndex = MeshComponent->RendererIndex;
        for (unsigned int i = 0; i < CMeshComponent::NumVertices; ++i)
        {
            const unsigned int CurrIndex = StartIndex + i;
            VertexData[CurrIndex].Position = *(MeshComponent->GetOwner()->GetTransform()) * CMeshComponent::BaseMeshVertices[i];
            VertexData[CurrIndex].Color = MeshComponent->Color;
        }
    }
}