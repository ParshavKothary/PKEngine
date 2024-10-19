#include <PongGame.h>
#include <Core/PKEngine.h>
#include <Core/PKCommon.h>
#include <EngineComponents/PKMeshComponent.h>
#include <Systems/PKSound.h>

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

            // Load all sounds
            Sounds.bounce = CAudioPlayer::Load("Assets/Sounds/bounce.wav");
            Sounds.score = CAudioPlayer::Load("Assets/Sounds/score.wav");
            Sounds.shoot = CAudioPlayer::Load("Assets/Sounds/shoot.wav");
            Sounds.win = CAudioPlayer::Load("Assets/Sounds/win.wav");

            // Start ball with player 1
            GivePlayerBall(0);
        }

        void CPongGame::ResetScore()
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
                CAudioPlayer::Play(Sounds.win);
                ResetScore();
            }
        }

        void CPongGame::GivePlayerBall(unsigned int player)
        {
            pPaddles[player]->GiveBall(pBall);
        }

        void CPongGame::OnHitWall(int player)
        {
            if (player < 0)
            {
                CAudioPlayer::Play(Sounds.bounce);
                return;
            }

            CAudioPlayer::Play(Sounds.score);
            assert(player == 0 || player == 1);
            IncrementScore(1 - player);
            GivePlayerBall(player);
        }

        void CPongGame::PlayPaddleBounceSound()
        {
            CAudioPlayer::Play(Sounds.shoot);
        }
    }
}