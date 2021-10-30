#ifndef PKEngine_PKEngine_H
#define PKEngine_PKEngine_H

#include <Core/PKBase.h>

namespace pkengine
{
	class CPKGame;
	class CGameObject;

	class CPKEngine
	{
	public:
		CPKEngine();
		~CPKEngine();

		void RunGame();

		CPKGame* GetGame() { return Game; }

		template<typename T>
		T* CreateGameObject(const char* InName);

		template<typename T>
		T* CreateGame(const int WindowWidth, const int WindowHeight, const char* GameTitle);

	private:

		void RegisterGame(CPKGame* Game, const char* GameName);
		bool InitSystems(const int WindowWidth, const int WindowHeight, const char* GameTitle);
		void RegisterGameObject(CGameObject* GameObject, const char* InName);

		bool bInit;
		bool bRunning;
		bool bShouldExit;

		CPKGame* Game;
	};

	template<typename T>
	inline T* CPKEngine::CreateGameObject(const char* InName)
	{
		assert(bInit);
		static_assert(std::is_base_of<CGameObject, T>()); // T needs to derive from CGameObject!

		T* NewObject = new T(Game);
		RegisterGameObject(NewObject, InName);
		return NewObject;
	}

	template<typename T>
	inline T* CPKEngine::CreateGame(const int WindowWidth, const int WindowHeight, const char* GameTitle)
	{
		static_assert(std::is_base_of<CPKGame, T>()); // T needs to derive from CPKGame!

		if (InitSystems(WindowWidth, WindowHeight, GameTitle) == false)
		{
			return nullptr;
		}

		T* NewGame = new T(this);
		RegisterGame(NewGame, GameTitle);
		return NewGame;
	}
}

#endif // !PKEngine_PKEngine_H