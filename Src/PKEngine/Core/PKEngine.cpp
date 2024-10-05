#include <Core/PKEngine.h>
#include <Game/PKGame.h>
#include <Game/PKGameObject.h>
#include <Game/PKBehaviour.h>
#include <Systems/PKInput.h>
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

        bInit = true;
        return true;
	}

    void CPKEngine::RegisterGame(CPKGame* InGame, const char* GameName)
    {
        Game = InGame;
        strcpy_s(Game->Name, GameName);

        InGame->Setup();
    }

    CPKEngine::CPKEngine()
    {
        bRunning = false;
        bShouldExit = false;
        bInit = false;
        Game = nullptr;
    }

	CPKEngine::~CPKEngine()
	{
        if (Game != nullptr)
        {
            delete Game;
        }

        CRenderer::Exit();
	}

	void CPKEngine::RunGame()
	{
        if (bInit == false)
        {
            std::cout << "Trying to RunGame before Init complete" << std::endl;
            return;
        }

        bRunning = true;
        CTime::GameStarted();

        while (bShouldExit == false)
        {
            // Input update
            glfwPollEvents();

            // Physics update

            for (CGameObject*& GameObject : Game->GameObjects)
            {
                GameObject->Update();
            }

            // Draw
            CRenderer::Draw();

            bShouldExit = glfwWindowShouldClose(CRenderer::GetWindow()) ||
                CInput::GetKeyUp(EKeyCode::KeyCode_ESCAPE);

            CInput::FlushInput(CRenderer::GetWindow());
            CTime::Tick();
        }
	}

    void CPKEngine::RegisterGameObject(CGameObject* GameObject, const char* InName)
    {
        strcpy_s(GameObject->Name, Game->GetAvailableGameObjectName(InName));
        Game->GameObjects.push_back(GameObject);
        GameObject->Setup();
    }
}