#include <PongGame.h>
#include <Core/PKEngine.h>
#include <Core/PKCommon.h>

#include <Objects/Ball.h>
#include <Objects/Paddle.h>
#include <Objects/Wall.h>

namespace pkengine
{
    namespace ponggame
    {
        void CPongGame::Setup()
        {
            CreateGameObject<CBall>("Ball");

            {
                CPaddle* Paddle = CreateGameObject<CPaddle>("Paddle");
                Paddle->GetTransform()->SetPosition(FVector3::Right() * 22.0f);
                Paddle->SetKeys(EKeyCode::KeyCode_UP, EKeyCode::KeyCode_DOWN);
            }

            {
                CPaddle* Paddle = CreateGameObject<CPaddle>("Paddle");
                Paddle->GetTransform()->SetPosition(FVector3::Right() * -22.0f);
            }

            {
                CWall* Wall = CreateGameObject<CWall>("Wall");
                Wall->GetTransform()->SetScale(FVector3(2.0f, 40.0f));
                Wall->GetTransform()->SetPosition(FVector3::Right() * -24.0f);
            }

            {
                CWall* Wall = CreateGameObject<CWall>("Wall");
                Wall->GetTransform()->SetScale(FVector3(2.0f, 40.0f));
                Wall->GetTransform()->SetPosition(FVector3::Right() * 24.0f);
            }

            {
                CWall* Wall = CreateGameObject<CWall>("Wall");
                Wall->GetTransform()->SetScale(FVector3(60.0f, 2.0f));
                Wall->GetTransform()->SetPosition(FVector3::Up() * -16.0f);
            }

            {
                CWall* Wall = CreateGameObject<CWall>("Wall");
                Wall->GetTransform()->SetScale(FVector3(60.0f, 2.0f));
                Wall->GetTransform()->SetPosition(FVector3::Up() * 16.0f);
            }
        }

        void CPongGame::OnP1Score()
        {
            ++p1Score;

            if (p1Score >= PONG_MAX_SCORE)
            {

            }
        }

        void CPongGame::OnP2Score()
        {

        }
    }
}