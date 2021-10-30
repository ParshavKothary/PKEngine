#ifndef PKENGINE_PKGAME_H
#define PKENGINE_PKGAME_H

#include <Core/PKBase.h>

namespace pkengine
{
	class CGameObject;
	class CPKEngine;

	class CPKGame
	{
		friend CPKEngine;

	public:

		CPKGame(CPKEngine* EngineContext);
		virtual ~CPKGame();

		inline CPKEngine* GetEngine() { return Engine; }

	protected:

		virtual void Setup() { }
		virtual void Tick() { }

		CPKEngine* Engine;
		char Name[32];
		std::list<CGameObject*> GameObjects;

	private:

		const char* GetAvailableGameObjectName(const char* InName);
	};
}

#endif // !PKENGINE_PKGAME_H
