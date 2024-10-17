#include <Core/PKEngine.h>
#include <EngineComponents/PKCamera.h>
#include <Game/PKGame.h>
#include <Game/PKGameObject.h>
#include <Game/PKBehaviour.h>
#include <Systems/PKInput.h>
#include <Systems/PKPhysics.h>
#include <Systems/PKRendering.h>
#include <Systems/PKTime.h>

namespace pkengine
{

	bool CPKEngine::InitSystems(const int WindowWidth, const int WindowHeight, const char* GameTitle)
	{
        if (CRenderer::Init(WindowWidth, WindowHeight, GameTitle) == false)
        {
            return false;
        }

        if (CInput::Init(CRenderer::GetWindow()) == false)
        {
            return false;
        }

        // init camera
        {
            Camera = new CCamera();
            Camera->SetPosition(FVector3());
            Camera->SetScale(50.0f);
            Camera->SetRotation(FVector3::Up());
        }

        bInit = true;
        return true;
	}

    void CPKEngine::OnGameCreated()
    {
        Game->Setup();
    }

    CPKEngine::CPKEngine()
    {
        bRunning = false;
        bShouldExit = false;
        bInit = false;
        Game = nullptr;
        Camera = nullptr;
    }

	CPKEngine::~CPKEngine()
	{
        if (Game != nullptr)
        {
            delete Game;
        }

        CRenderer::Exit();

        if (bInit)
        {
            delete Camera;
        }

        bInit = false;
	}

	void CPKEngine::RunGame()
	{
        if (bInit == false)
        {
            std::cout << "Trying to RunGame before Init complete" << std::endl;
            return;
        }

        if (Game == nullptr)
        {
            std::cout << "Trying to RunGame but Game is null!" << std::endl;
            return;
        }

        bRunning = true;
        CTime::Start();
        Game->Start();

        while (bShouldExit == false)
        {
            CInput::Update();

            CPhysics::Update();

            Game->Update();

            CRenderer::Update(Camera->GetTransform());

            bShouldExit = glfwWindowShouldClose(CRenderer::GetWindow()) ||
                CInput::GetKeyUp(EKeyCode::KeyCode_ESCAPE);

            CInput::FlushInput(CRenderer::GetWindow());
            CTime::Update();
        }
	}
}