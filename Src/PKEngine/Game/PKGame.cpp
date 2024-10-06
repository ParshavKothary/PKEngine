#include <Game/PKGame.h>
#include <Game/PKGameObject.h>

namespace pkengine
{
	CGame::CGame(CPKEngine* EngineContext)
	{
		assert(EngineContext != nullptr);
		Engine = EngineContext;
		GameObjects = std::list<CGameObject*>();
	}

	CGame::~CGame()
	{
		while (GameObjects.empty() == false)
		{
			delete GameObjects.front();
			GameObjects.pop_front();
		}
	}

	void CGame::Start()
	{
		for (CGameObject*& GameObject : GameObjects)
		{
			GameObject->Start();
		}
	}

	void CGame::Update()
	{
		for (CGameObject*& GameObject : GameObjects)
		{
			GameObject->Update();
		}
	}

	const char* CGame::GetAvailableGameObjectName(const char* InName)
	{
		return InName;
	}

	void CGame::RegisterGameObject(CGameObject* GameObject, const char* InName)
	{
		GameObject->SetName(GetAvailableGameObjectName(InName));
		GameObject->Setup();
		GameObjects.push_back(GameObject);
	}
}