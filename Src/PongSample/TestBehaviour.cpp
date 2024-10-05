#include <TestBehaviour.h>
#include <MovementBehaviour.h>
#include <Core/PKCommon.h>

namespace pkengine
{
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
	}
}