#ifndef PKENGINE_PONGGAME_PONGGAME_H
#define PKENGINE_PONGGAME_PONGGAME_H

#include <Game/PKGame.h>

namespace pkengine
{
	class CAudioClip;
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
		protected:

			struct FSounds
			{
				const CAudioClip* bounce;
				const CAudioClip* shoot;
				const CAudioClip* score;
				const CAudioClip* win;
			};

			CPaddle* pPaddles[2];
			CBallMove* pBall;

			unsigned int scores[2];
			CMeshComponent* scoreIcons[2][PONG_MAX_SCORE];

			FSounds Sounds;

			void Setup() override;
			void ResetScore();
			void IncrementScore(unsigned int player);
		void GivePlayerBall(unsigned int player); 
		
		public:
			CPongGame(CPKEngine* EngineContext) :
				CGame(EngineContext),
				pBall(nullptr)
			{
				memset(scoreIcons[0], 0, sizeof(void*) * PONG_MAX_SCORE);
				memset(scoreIcons[1], 0, sizeof(void*) * PONG_MAX_SCORE);
				memset(scores, 0, sizeof(unsigned int) * 2);
				memset(&Sounds, 0, sizeof(FSounds));
			}

			void OnHitWall(int player);
			void PlayPaddleBounceSound();
		};
	}
}

#endif // !PKENGINE_PONGGAME_PONGGAME_H