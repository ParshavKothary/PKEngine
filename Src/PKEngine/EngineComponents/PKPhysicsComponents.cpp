#include <EngineComponents/PKPhysicsComponents.h>
#include <Game/PKGameObject.h>
#include <Systems/PKPhysics.h>

namespace pkengine
{
	CCollider::CCollider(CGameObject* InOwner) : CBehaviour(InOwner)
	{
		max = FVector3(0.5f, 0.5f, 0.0f);
		min = max * -1.0f;

		CollisionHandlers = containers::list<CCollisionHandler*>();
	}

	void CCollider::SetSizeAndOffset(const FVector3& size, const FVector3& offset)
	{
		max = (size * 0.5f) + offset;
		min = (size * -0.5f) + offset;
	}

	bool CCollider::CheckConstruct()
	{
		return CPhysics::RegisterCollider(this);
	}

	void CCollider::AddHandler(CCollisionHandler* Handler)
	{
		assert(Handler != nullptr);
		CollisionHandlers.push_back(Handler);
	}

	void CCollider::OnCollision(const FCollision& collision)
	{
		for (CCollisionHandler* Handler : CollisionHandlers)
		{
			Handler->OnCollision(collision);
		}
	}

	void CCollider::UpdatePoints()
	{
		FTransform& xform = *(GetOwner()->GetTransform());

		points[0] = FVector3(min.GetX(), max.GetY(), 0.0f);
		points[1] = FVector3(max.GetX(), min.GetY(), 0.0f);
		points[2] = max;
		points[3] = min;

		for (FVector3& point : points)
		{
			point = xform * point;
		}
	}

	void CCollisionHandler::Start()
	{
		CCollider* OwnerCollider = Owner->GetBehaviour<CCollider>();
		if (OwnerCollider == nullptr)
		{
			std::cout << "Error: Trying to add Collision handler to " << Owner->GetName() << " but no Collider added" << std::endl;
			return;
		}

		OwnerCollider->AddHandler(this);
	}
}