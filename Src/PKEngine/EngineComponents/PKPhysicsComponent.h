#ifndef PKENGINE_PKPHYSICSCOMPONENT_H
#define PKENGINE_PKPHYSICSCOMPONENT_H

#include <Core/PKBase.h>
#include <Game/PKBehaviour.h>

namespace pkengine
{
	class CPhysicsComponent : public CBehaviour_Internal
	{
	public:
		CPhysicsComponent(CGameObject* InOwner) : CBehaviour_Internal(InOwner) {}

		virtual void OnCollision() {}
	};
}

#endif // !PKENGINE_PKPHYSICSCOMPONENT_H
