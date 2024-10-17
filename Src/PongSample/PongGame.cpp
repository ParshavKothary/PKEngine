#include <PongGame.h>
#include <Core/PKEngine.h>
#include <Core/PKCommon.h>
#include <EngineComponents/PKMeshComponent.h>

#include <Behaviours/BallMove.h>
#include <Objects/Ball.h>
#include <Objects/Paddle.h>
#include <Objects/Wall.h>

namespace pkengine
{
    namespace ponggame
    {
        void CPongGame::Setup()
        {
            // Create Ball
            CGameObject* pObj = CreateGameObject<CBall>("Ball");
            pBall = pObj->GetBehaviour<CBallMove>();

            float mults[2] = { -1.0f, 1.0f };

            for (int ii = 0; ii < 2; ++ii)
            {
                // Create Paddles
                CPaddle* Paddle = CreateGameObject<CPaddle>("Paddle");
                Paddle->GetTransform()->SetPosition(FVector3::Right() * 22.0f * mults[ii]);
                Paddle->SetPlayer(ii);
                pPaddles[ii] = Paddle;

                // Create walls
                CWall* xWall = CreateGameObject<CWall>("Wall");
                xWall->GetTransform()->SetScale(FVector3(2.0f, 40.0f));
                xWall->GetTransform()->SetPosition(FVector3::Right() * 24.0f * mults[ii]);
                xWall->SetPlayerWall(ii);

                CWall* yWall = CreateGameObject<CWall>("Wall");
                yWall->GetTransform()->SetScale(FVector3(60.0f, 2.0f));
                yWall->GetTransform()->SetPosition(FVector3::Up() * 16.0f * mults[ii]);

                // Create score icons
                for (int jj = 0; jj < PONG_MAX_SCORE; ++jj)
                {
                    CGameObject* icon = CreateGameObject<CGameObject>("icon");
                    scoreIcons[ii][jj] = icon->AddMeshComponent(EMeshType::Quad, FVector3(0.3f, 0.3f, 0.3f));

                    FVector3 pos = (FVector3::Up() * 13.0f) + (FVector3::Right() * 18.0f * mults[ii]) + (FVector3::Left() * 2.0f * mults[ii] * (float)jj);
                    icon->GetTransform()->SetPosition(pos);
                }
            }

            GivePlayerBall(0);
        }

        void CPongGame::Reset()
        {
            for (int ii = 0; ii < 2; ++ii)
            {
                scores[ii] = 0;

                for (int jj = 0; jj < PONG_MAX_SCORE; ++jj)
                {
                    scoreIcons[ii][jj]->SetColor(FVector3(0.3f, 0.3f, 0.3f));
                }
            }
        }

        void CPongGame::IncrementScore(unsigned int player)
        {
            scoreIcons[player][scores[player]]->SetColor(FVector3(1.0f, 1.0f, 1.0f));

            ++(scores[player]);

            if (scores[player] >= PONG_MAX_SCORE)
            {
                Reset();
            }
        }

        void CPongGame::GivePlayerBall(unsigned int player)
        {
            pPaddles[player]->GiveBall(pBall);
        }

        void CPongGame::OnHitPlayerWall(unsigned int player)
        {
            assert(player == 0 || player == 1);
            IncrementScore(1 - player);
            GivePlayerBall(player);
        }
    }
}