#include "BallMove.h"
#include <EngineComponents/PKPhysicsComponents.h>
#include <Objects/Paddle.h>
#include <Objects/Wall.h>
#include <Systems/PKTime.h>

namespace pkengine
{
	namespace ponggame
	{
		void CBallMove::OnCollision(const FCollision& collision)
		{
			CPaddle* paddle = dynamic_cast<CPaddle*>(collision.collider->GetOwner());
			if (paddle != nullptr)
			{
				moveDir = moveDir.Reflect(collision.normal);
				moveDir += paddle->GetUpDir() * FVector3::Up() * 0.3f;
				if (abs(moveDir.GetY()) > 0.6f)
				{
					moveDir.SetY(moveDir.GetY() > 0.0f ? 0.6f : -0.6f);
				}
				moveDir.Normalize();

				return;
			}

			CWall* wall = dynamic_cast<CWall*>(collision.collider->GetOwner());
			if (wall != nullptr)
			{
				moveDir = moveDir.Reflect(collision.normal);
			}
		}

		void CBallMove::Update()
		{
			CCollisionHandler::Update();

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