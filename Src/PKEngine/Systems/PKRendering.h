#ifndef PKENGINE_PKRENDERING_H
#define PKENGINE_PKRENDERING_H

#include <Core/PKBase.h>
#include <GLFW/glfw3.h>

namespace pkengine
{
	class CGameObject;
	class CMeshComponent;

	struct FVertexData
	{
		FVector3 Position;
		FVector3 Color;
	};

	class CRenderer
	{
	public:
		static inline GLFWwindow* GetWindow()
		{
			assert(bInit());
			return Instance->Window;
		}

		static inline bool bInit() { return Instance != nullptr; }

		static bool Init(const int WindowWidth, const int WindowHeight, const char* WindowTitle);
		static void Exit();

		static bool RegisterMesh(CMeshComponent* MeshComponent);
		static void UnregisterMesh(CMeshComponent* MeshComponent);

		static void Update();

	private:

		static const char* VertexShaderSource;
		static const char* FragmentShaderSource;
		static CRenderer* Instance;

		static bool ShaderCompileCheck(const unsigned int& ShaderObj, const GLenum Status);

		CRenderer(const int WindowWidth, const int WindowHeight, const char* WindowTitle);
		~CRenderer();

		void CleanUp();

		bool AddMeshToBuffer(CMeshComponent* MeshComponent);
		void RemoveMeshFromBuffer(CMeshComponent* MeshComponent);
		void TransformAndCopyMeshVertices(CMeshComponent* MeshComponent);

		void InternalDraw();

		GLFWwindow* Window;

		unsigned int ShaderProgram;
		unsigned int VBO;
		unsigned int VAO;

		std::list<CMeshComponent*> MeshComponents;
		std::vector<FVertexData> VertexData;
		unsigned int NumActiveVerts;
	};
}

#endif // !PKENGINE_PKRENDERING_H