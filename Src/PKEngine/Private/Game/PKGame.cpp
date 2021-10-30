#include <Game/PKGame.h>
#include <Game/PKGameObject.h>

namespace pkengine
{
	CPKGame::CPKGame(CPKEngine* EngineContext)
	{
		assert(EngineContext != nullptr);
		Engine = EngineContext;
		GameObjects = std::list<CGameObject*>();
	}

	CPKGame::~CPKGame()
	{
		while (GameObjects.empty() == false)
		{
			delete GameObjects.front();
			GameObjects.pop_front();
		}
	}

	const char* CPKGame::GetAvailableGameObjectName(const char* InName)
	{
		return InName;
	}
}