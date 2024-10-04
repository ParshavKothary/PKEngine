#ifndef PKENGINE_PONGGAME_MOVEMENTBEHAVIOUR_H
#define PKENGINE_PONGGAME_MOVEMENTBEHAVIOUR_H

#include <Game/PKBehaviour.h>
#include <Core/PKBase.h>

namespace pkengine
{
	class CMovementBehaviour : public CPKBehaviour
	{
	public:
		CMovementBehaviour(CGameObject* InOwner);

		EKeyCode LeftKey;
		EKeyCode RightKey;
		EKeyCode UpKey;
		EKeyCode DownKey;
		EKeyCode RotateCWKey;
		EKeyCode RotateCCWKey;

		void AddMoveSpeed(int dir);

	protected:

		virtual void Update() override;
		void HandleMove();
		void HandleRotate();

		float MoveSpeed;
	};
}

#endif // !PKENGINE_PONGGAME_MOVEMENTBEHAVIOUR_H
