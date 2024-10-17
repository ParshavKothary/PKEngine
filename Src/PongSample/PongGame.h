#ifndef PKENGINE_PONGGAME_PONGGAME_H
#define PKENGINE_PONGGAME_PONGGAME_H

#include <Game/PKGame.h>

namespace pkengine
{
	class CGameObject;
	class CMeshComponent;
	class CPKEngine;

	namespace ponggame
	{
#define PONG_MAX_SCORE 5

		class CBallMove;
		class CPaddle;

		class CPongGame : public CGame
		{
		public:
			CPongGame(CPKEngine* EngineContext) :
				CGame(EngineContext),
				pBall(nullptr)
			{
				memset(scoreIcons[0], 0, sizeof(void*) * PONG_MAX_SCORE);
				memset(scoreIcons[1], 0, sizeof(void*) * PONG_MAX_SCORE);
				memset(scores, 0, sizeof(unsigned int) * 2);
			}

			void OnHitPlayerWall(unsigned int player);

		protected:

			CPaddle* pPaddles[2];
			CBallMove* pBall;

			unsigned int scores[2];
			CMeshComponent* scoreIcons[2][PONG_MAX_SCORE];

			void Setup() override;
			void Reset();
			void IncrementScore(unsigned int player);
			void GivePlayerBall(unsigned int player);
		};
	}
}

#endif // !PKENGINE_PONGGAME_PONGGAME_H