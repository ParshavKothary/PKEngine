#ifndef PKENGINE_PKPHYSICSCOMPONENTS_H
#define PKENGINE_PKPHYSICSCOMPONENTS_H

#include <Core/PKBase.h>
#include <Game/PKBehaviour.h>

namespace pkengine
{
	class CCollisionHandler;

	class CCollider : public CBehaviour
	{
	public:
		CCollider(CGameObject* InOwner);

		virtual void SetSizeAndOffset(const FVector3& size, const FVector3& offset);
		virtual bool CheckConstruct() override;
		virtual void AddHandler(CCollisionHandler* Handler);

	protected:
		FVector3 max;
		FVector3 min;

		containers::list<CCollisionHandler*> CollisionHandlers;;
	};

	class CCollisionHandler : public CBehaviour
	{
	public:
		CCollisionHandler(CGameObject* InOwner) : CBehaviour(InOwner) {}

		virtual void OnCollision(const FCollision& collision) {}
		virtual void Start() override;

	protected:
		FVector3 max;
		FVector3 min;
	};
}

#endif // !PKENGINE_PKPHYSICSCOMPONENTS_H
