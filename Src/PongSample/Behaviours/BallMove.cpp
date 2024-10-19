#include "BallMove.h"
#include <EngineComponents/PKPhysicsComponents.h>
#include <Objects/Paddle.h>
#include <Objects/Wall.h>
#include <Systems/PKTime.h>

#include <PongGame.h>

namespace pkengine
{
	namespace ponggame
	{
		void CBallMove::TakePlayerUpVel(float dir)
		{
			if (dir == 0.0f) return;

			moveDir += dir * FVector3::Up() * 0.3f;
			if (abs(moveDir.GetY()) > 0.6f)
			{
				moveDir.SetY(moveDir.GetY() > 0.0f ? 0.6f : -0.6f);
			}
			moveDir.Normalize();
		}

		void CBallMove::OnCollision(const FCollision& collision)
		{
			moveDir = moveDir.Reflect(collision.normal);

			CPaddle* paddle = dynamic_cast<CPaddle*>(collision.collider->GetOwner());
			if (paddle != nullptr)
			{
				this->GetOwner()->GetGame<CPongGame>()->PlayPaddleBounceSound();
				TakePlayerUpVel(paddle->GetUpDir());
				return;
			}

			CWall* wall = dynamic_cast<CWall*>(collision.collider->GetOwner());
			if (wall != nullptr)
			{
				CPongGame* PongGame = this->GetOwner()->GetGame<CPongGame>();
				PongGame->OnHitWall(wall->GetPlayerWall());
			}
		}

		void CBallMove::Update()
		{
			CCollisionHandler::Update();

			if (IsGrabbed)
			{
				return;
			}

			FTransform* xform = GetOwner()->GetTransform();
			xform->SetPosition(xform->GetPosition() + moveDir * 25.0f * CTime::GetDeltaTime());
		}

		void CBallMove::Start()
		{
			CCollisionHandler::Start();

			moveDir = FVector3::Right();
		}
	}
}