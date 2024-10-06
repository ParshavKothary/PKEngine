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