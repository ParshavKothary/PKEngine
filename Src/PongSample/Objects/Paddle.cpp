#include "Paddle.h"
#include <Systems/PKInput.h>
#include <Systems/PKTime.h>

#define PADDLE_MAX_Y 12

namespace pkengine
{
	namespace ponggame
	{
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
	}
}