#ifndef PKENGINE_PKPHYSICSCOMPONENTS_H
#define PKENGINE_PKPHYSICSCOMPONENTS_H

#include <Core/PKBase.h>
#include <Game/PKBehaviour.h>

namespace pkengine
{
	class CCollider : public CBehaviour
	{
	public:
		CCollider(CGameObject* InOwner) : CBehaviour(InOwner) {}

		virtual void SetSizeAndOffset(const FVector3& size, const FVector3& offset);
		virtual bool CheckConstruct() override;

	protected:
		FVector3 max;
		FVector3 min;
	};

	class CCollisionHandler : public CBehaviour
	{
	public:
		CCollisionHandler(CGameObject* InOwner) : CBehaviour(InOwner) {}

		virtual void OnCollision() {}

	protected:
		FVector3 max;
		FVector3 min;
	};
}

#endif // !PKENGINE_PKPHYSICSCOMPONENTS_H
