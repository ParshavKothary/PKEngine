#ifndef PKENGINE_PKGAME_H
#define PKENGINE_PKGAME_H

#include <Core/PKBase.h>

namespace pkengine
{
	class CGameObject;
	class CPKEngine;

	class CGame
	{
		friend CPKEngine;

	public:

		CGame(CPKEngine* EngineContext);
		virtual ~CGame();

		inline CPKEngine* GetEngine() { return Engine; }

		template<typename T>
		T* CreateGameObject(const char* InName);

	protected:

		virtual void Setup() { }
		virtual void Start();
		virtual void Update();

		CPKEngine* Engine;
		containers::list<CGameObject*> GameObjects;

	private:

		void RegisterGameObject(CGameObject* GameObject, const char* InName);
		const char* GetAvailableGameObjectName(const char* InName);
	};

	template<typename T>
	T* CGame::CreateGameObject(const char* InName)
	{
		static_assert(std::is_base_of<CGameObject, T>()); // T needs to derive from CGameObject!

		T* NewObject = new T(this);
		RegisterGameObject(NewObject, InName);
		return NewObject;
	}
}

#endif // !PKENGINE_PKGAME_H
