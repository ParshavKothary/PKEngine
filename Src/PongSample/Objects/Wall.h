#pragma once
#ifndef PKENGINE_PONGGAME_WALL_H
#define PKENGINE_PONGGAME_WALL_H

#include <Core/PKBase.h>
#include <Game/PKGameObject.h>

namespace pkengine
{
	namespace ponggame
	{
		class CWall : public CGameObject
		{

		protected:
			int playerWall;

		public:
			CWall(CGame* GameContext):
				CGameObject(GameContext),
				playerWall(-1)
			{}

			virtual void Setup() override;

			inline int GetPlayerWall() { return playerWall; }
			inline void SetPlayerWall(int inPlayerWall) { playerWall = inPlayerWall; }
		};
	}
}

#endif