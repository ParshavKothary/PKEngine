#include <TestBehaviour.h>
#include <MovementBehaviour.h>
#include <Core/PKCommon.h>
#include <EngineComponents/PKMeshComponent.h>

namespace pkengine
{
	void CTestBehaviour::OnCollision(const FCollision& collision)
	{
		isColliding = true;
		if (DebugTransform != nullptr)
		{
			DebugTransform->SetPosition(collision.point);
			DebugTransform2->SetPosition(collision.point + (collision.normal * 0.5f));
			DebugTransform2->SetRotation(collision.normal);
		}
	}
	void CTestBehaviour::Update()
	{
		int speedDir = 0;
		if (CInput::GetKeyUp(EKeyCode::KeyCode_UP)) speedDir = 1;
		else if (CInput::GetKeyUp(EKeyCode::KeyCode_DOWN)) speedDir = -1;

		if (speedDir != 0)
		{
			CMovementBehaviour* moveBehaviour = Owner->GetBehaviour<CMovementBehaviour>();
			if (moveBehaviour != nullptr)
			{
				moveBehaviour->AddMoveSpeed(speedDir);
			}
		}

		DebugMesh->SetColor(isColliding ? FVector3(0.0f, 1.0f, 0.0f) : FVector3(1.0f, 0.0f, 0.0f));
		isColliding = false;
	}
}