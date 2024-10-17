#pragma once
#ifndef PKENGINE_PONGGAME_BALLMOVE_H
#define PKENGINE_PONGGAME_BALLMOVE_H

#include <Game/PKBehaviour.h>
#include <EngineComponents/PKPhysicsComponents.h>

namespace pkengine
{
	namespace ponggame
	{
		class CBallMove : public CCollisionHandler
		{

		protected:

			bool IsGrabbed;
			FVector3 moveDir;

		public:
			CBallMove(CGameObject* InOwner) :
				CCollisionHandler(InOwner),
				IsGrabbed(true)
			{}

			virtual void OnCollision(const FCollision& collision) override;
			virtual void Update() override;
			virtual void Start() override;

			inline void SetIsGrabbed(bool bGrabbed) { IsGrabbed = bGrabbed; }
			inline void SetMoveDir(const FVector3& dir) { moveDir = dir; }

			void TakePlayerUpVel(float dir);
		};
	}
}

#endif // !PKENGINE_PONGGAME_BALLMOVE_H
