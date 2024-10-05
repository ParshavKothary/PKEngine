#include <MovementBehaviour.h>
#include <Core/PKCommon.h>

namespace pkengine
{
	CMovementBehaviour::CMovementBehaviour(CGameObject* InOwner) : CPKBehaviour(InOwner)
	{
		LeftKey = EKeyCode::KeyCode_A;
		RightKey = EKeyCode::KeyCode_D;
		UpKey = EKeyCode::KeyCode_W;
		DownKey = EKeyCode::KeyCode_S;
		RotateCWKey = EKeyCode::KeyCode_E;
		RotateCCWKey = EKeyCode::KeyCode_Q;

		MoveSpeed = 0.5f;
	}

	void CMovementBehaviour::AddMoveSpeed(int dir)
	{
		MoveSpeed += (float)dir * 0.25f;
		MoveSpeed = std::clamp(MoveSpeed, 0.25f, 1.0f);
	}

	void CMovementBehaviour::Update()
	{
		HandleMove();
		HandleRotate();
	}

	void CMovementBehaviour::HandleMove()
	{
		float RightDir = 0.0f;
		float UpDir = 0.0f;

		if (CInput::GetKey(LeftKey)) RightDir = -1.0f;
		else if (CInput::GetKey(RightKey)) RightDir = 1.0f;

		if (CInput::GetKey(UpKey)) UpDir = 1.0f;
		else if (CInput::GetKey(DownKey)) UpDir = -1.0f;

		if (RightDir == 0.0f && UpDir == 0.0f) return;

		FVector3 Translation = Owner->GetTransform()->GetUp() * UpDir * CTime::GetDeltaTime() * MoveSpeed;
		Owner->GetTransform()->SetPosition((Owner->GetTransform()->GetPosition() + Translation));
	}
	
	void CMovementBehaviour::HandleRotate()
	{
		float Rotation = 0.0f;

		if (CInput::GetKey(RightKey)) Rotation = 1.0f;
		else if (CInput::GetKey(LeftKey)) Rotation = -1.0f;

		if (Rotation == 0.0f) return;

		Owner->GetTransform()->Rotate(Rotation * CTime::GetDeltaTime() * MoveSpeed * 5.0f, FVector3::Backward());
	}
}