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
		public:
			CBallMove(CGameObject* InOwner) :
				CCollisionHandler(InOwner)
			{}

			virtual void OnCollision(const FCollision& collision) override;
			virtual void Update() override;
			virtual void Start() override;

		protected:
			
			FVector3 moveDir;
		};
	}
}

#endif // !PKENGINE_PONGGAME_BALLMOVE_H
