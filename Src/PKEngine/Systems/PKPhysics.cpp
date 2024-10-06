#include <Systems/PKPhysics.h>

namespace pkengine
{
#define MAX_COLLIDERS 100

	CPhysics::IColliderList CPhysics::Colliders = CPhysics::IColliderList();
	CPhysics::ICollisionMap CPhysics::CollisionMap = CPhysics::ICollisionMap();
	unsigned int CPhysics::NumColliders = 0;

	void CPhysics::Update()
	{
		for (IColliderList::iterator iter = Colliders.begin(); iter != Colliders.end();)
		{
			CCollider* ColliderA = *iter;
			++iter;
			for (IColliderList::iterator iter2 = iter; iter2 != Colliders.end(); ++iter2)
			{
				CCollider* ColliderB = *iter2;

				FVector3 point;
				FVector3 normal;
				bool isColliding = false; // DO COLLISION CHECK!
				if (isColliding)
				{
					AddToCollisionMap(ColliderA, ColliderB, point, normal);
					AddToCollisionMap(ColliderB, ColliderA, point, -normal);
				}
				else
				{
					RemoveFromCollisionMap(ColliderA, ColliderB);
					RemoveFromCollisionMap(ColliderB, ColliderA);
				}
			}
		}
	}

	void CPhysics::PostUpdate()
	{
		CollisionMap.clear();
	}

	bool CPhysics::RegisterCollider(CCollider* Collider)
	{
		if (NumColliders + 1 >= MAX_COLLIDERS)
		{
			return false;
		}

		++NumColliders;
		Colliders.emplace(Collider);
		return true;
	}

	void CPhysics::UnregisterCollider(CCollider* Collider)
	{
		assert(NumColliders > 0);
		--NumColliders;
		Colliders.erase(Collider);
	}

	void CPhysics::AddToCollisionMap(CCollider* key, CCollider* collider, const FVector3& point, const FVector3& normal)
	{
		if (CollisionMap.find(key) == CollisionMap.end())
		{
			CollisionMap.emplace(key, ICollidersCollisions());
		}

		CollisionMap[key].emplace(collider, FCollision(collider, point, normal));
	}

	void CPhysics::RemoveFromCollisionMap(CCollider* key, CCollider* collider)
	{
		ICollisionMap::iterator collisionsEntry = CollisionMap.find(key);
		if (collisionsEntry == CollisionMap.end())
		{
			return;
		}

		ICollidersCollisions& collisions = collisionsEntry->second;
		ICollidersCollisions::iterator iter = collisions.find(collider);
		if (iter == collisions.end())
		{
			return;
		}

		collisions.erase(iter);
		if (collisions.empty())
		{
			CollisionMap.erase(collisionsEntry);
		}
	}
}