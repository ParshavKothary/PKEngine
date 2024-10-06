#ifndef PKENGINE_PKENGINE_H
#define PKENGINE_PKENGINE_H

#include <Core/PKBase.h>

namespace pkengine
{
	class CGame;
	class CGameObject;

	class CPKEngine
	{
	public:
		CPKEngine();
		~CPKEngine();

		void RunGame();

		CGame* GetGame() { return Game; }

		template<typename T>
		T* CreateGame(const int WindowWidth, const int WindowHeight, const char* GameTitle);

	private:

		void OnGameCreated();
		bool InitSystems(const int WindowWidth, const int WindowHeight, const char* GameTitle);

		bool bInit;
		bool bRunning;
		bool bShouldExit;

		CGame* Game;
	};

	template<typename T>
	inline T* CPKEngine::CreateGame(const int WindowWidth, const int WindowHeight, const char* GameTitle)
	{
		static_assert(std::is_base_of<CGame, T>()); // T needs to derive from CGame!

		if (Game != nullptr)
		{
			std::cout << "Error: trying to create multiple games!!" << std::endl;
			return nullptr;
		}

		if (InitSystems(WindowWidth, WindowHeight, GameTitle) == false)
		{
			return nullptr;
		}

		T* NewGame = new T(this);
		Game = NewGame;
		OnGameCreated();
		return NewGame;
	}
}

#endif // !PKENGINE_PKENGINE_H