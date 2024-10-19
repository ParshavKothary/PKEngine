#include "Paddle.h"
#include <Systems/PKInput.h>
#include <Systems/PKTime.h>
#include <Behaviours/BallMove.h>
#include <PongGame.h>

#define PADDLE_MAX_Y 12

namespace pkengine
{
	namespace ponggame
	{
		void CPaddle::UpdateMove()
		{
			upDir = 0.0f;
			if (CInput::GetKey(upKey)) upDir = 1.0f;
			else if (CInput::GetKey(downKey)) upDir = -1.0f;

			if (upDir == 0.0f) return;

			GetTransform()->SetPosition(GetTransform()->GetPosition() + FVector3::Up() * upDir * 15.0f * CTime::GetDeltaTime());

			FVector3 pos = GetTransform()->GetPosition();
			if (fabsf(pos.GetY()) > PADDLE_MAX_Y)
			{
				pos.SetY(PADDLE_MAX_Y * (pos.GetY() > 0 ? 1.0f : -1.0f));
				GetTransform()->SetPosition(pos);
			}
		}

		void CPaddle::UpdateShoot()
		{
			if (CInput::GetKeyUp(shootKey))
			{
				ShootBall();
			}
		}

		void CPaddle::Setup()
		{
			CGameObject::Setup();

			GetTransform()->SetScale(FVector3(1.0f, 6.0f, 1.0f));
			AddMeshComponent(EMeshType::Quad, FVector3(0.8f, 0.8f, 0.8f));
			AddCollider();
		}

		void CPaddle::Update()
		{
			CGameObject::Update();
			UpdateMove();
			if (Ball != nullptr)
			{
				FVector3 ballPos = GetTransform()->GetPosition() + (shootDir * 2.0f);
				Ball->GetOwner()->GetTransform()->SetPosition(ballPos);

				UpdateShoot();
			}
		}

		void CPaddle::SetPlayer(unsigned int player)
		{
			EKeyCode upKeys[2] = { EKeyCode::KeyCode_W, EKeyCode::KeyCode_UP };
			EKeyCode downKeys[2] = { EKeyCode::KeyCode_S, EKeyCode::KeyCode_DOWN };
			EKeyCode shootKeys[2] = { EKeyCode::KeyCode_D, EKeyCode::KeyCode_LEFT };
			FVector3 shootDirs[2] = { FVector3::Right(), FVector3::Left() };

			upKey = upKeys[player];
			downKey = downKeys[player];
			shootKey = shootKeys[player];
			shootDir = shootDirs[player];
		}

		void CPaddle::GiveBall(CBallMove* inBall)
		{
			Ball = inBall;
			Ball->SetIsGrabbed(true);
		}

		void CPaddle::ShootBall()
		{
			Ball->SetMoveDir(shootDir);
			Ball->TakePlayerUpVel(upDir);
			Ball->SetIsGrabbed(false);
			Ball = nullptr;
			GetGame<CPongGame>()->PlayPaddleBounceSound();
		}
	}
}