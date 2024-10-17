#ifndef PKENGINE_PONGGAME_PONGGAME_H
#define PKENGINE_PONGGAME_PONGGAME_H

#include <Game/PKGame.h>

namespace pkengine
{
	class CPKEngine;
	class CGameObject;
	class CMeshComponent;

	namespace ponggame
	{
#define PONG_MAX_SCORE 5
		class CPongGame : public CGame
		{
		public:
			CPongGame(CPKEngine* EngineContext) :
				CGame(EngineContext),
				p1Score(0),
				p2Score(0),
				pBall(nullptr)
			{
				memset(p1Hearts, 0, sizeof(void*) * PONG_MAX_SCORE);
				memset(p2Hearts, 0, sizeof(void*) * PONG_MAX_SCORE);
			}

			void OnP1Score();
			void OnP2Score();

		protected:

			unsigned int p1Score;
			unsigned int p2Score;

			CGameObject* pBall;
			CMeshComponent* p1Hearts[PONG_MAX_SCORE];
			CMeshComponent* p2Hearts[PONG_MAX_SCORE];

			void Setup() override;
		};
	}
}

#endif // !PKENGINE_PONGGAME_PONGGAME_H