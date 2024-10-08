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
		typedef FVector3 PointCollection[4];

		CCollider(CGameObject* InOwner);

		virtual void SetSizeAndOffset(const FVector3& size, const FVector3& offset);
		virtual bool CheckConstruct() override;
		virtual void AddHandler(CCollisionHandler* Handler);
		virtual void OnCollision(const FCollision& collision);

		inline FVector3 GetMax() const { return max; }
		inline FVector3 GetMin() const { return min; }

		inline const PointCollection& GetPoints() const { return points; }

		void UpdatePoints();

	protected:
		FVector3 max;
		FVector3 min;

		FVector3 points[4];

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
