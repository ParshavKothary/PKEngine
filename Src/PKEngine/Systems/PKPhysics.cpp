#include <Systems/PKPhysics.h>

#include <EngineComponents/PKPhysicsComponents.h>
#include <Game/PKGameObject.h>

namespace pkengine
{
#define MAX_COLLIDERS 100

	CPhysics::IColliderList CPhysics::Colliders = CPhysics::IColliderList();
	CPhysics::ICollisionMap CPhysics::CollisionMap = CPhysics::ICollisionMap();
	unsigned int CPhysics::NumColliders = 0;

	struct FTestNormal
	{
		FVector3 n;
		bool isA;

		FTestNormal(const FVector3& inn, const bool inisA) :
			n(inn), isA(inisA) {}
	};

	struct FProjResult
	{
		FVector3 minPoint;
		FVector3 maxPoint;

		bool isEdge;

		FProjResult() :
			minPoint(),
			maxPoint(),
			isEdge(false)
		{}
	};

	struct FOverlap
	{
		FVector3 point;
		FVector3 normal;
		float overlap;
		bool isEdgeEdge;

		FOverlap() :
			point(),
			normal(1.0f, 0.0f),
			overlap(-1.0f),
			isEdgeEdge(false) {}
	};

	// returns min/max points along axis, and if they are edges
	FProjResult GetProj(const CCollider* Collider, const FVector3& axis, float& min, float& max)
	{
		const FVector3(&points)[4] = Collider->GetPoints();

		FProjResult result;
		result.minPoint = points[0];
		result.maxPoint = points[0];
		min = result.minPoint.Dot(axis);
		max = min;

		for (const FVector3& point : points)
		{
			float dot = point.Dot(axis);
			if (dot < min)
			{
				min = dot;
				result.minPoint = point;
			}
			if (dot > max)
			{
				max = dot;
				result.maxPoint = point;
			}
		}

		// check if edge
		{
			const FVector3 up = Collider->GetOwner()->GetTransform()->GetUp();
			const float dot = fabsf(up.Dot(axis));
			result.isEdge = pkfloat::IsClose(dot, 1.0f) || pkfloat::IsClose(dot, 0.0f);
		}

		return result;
	}

	// returns amount of overlap, normal and point
	FOverlap GetOverlap(const CCollider* ColliderA, CCollider* ColliderB, const FTestNormal& testNormal)
	{
		FOverlap result;

		float minA, maxA, minB, maxB;
		FProjResult projResA = GetProj(ColliderA, testNormal.n, minA, maxA);
		FProjResult projResB = GetProj(ColliderB, testNormal.n, minB, maxB);

		result.normal = testNormal.n;
		result.isEdgeEdge = projResB.isEdge && projResA.isEdge;

		if (minA <= maxB && minA >= minB)
		{
			result.overlap = maxB - minA;
			result.point = testNormal.isA ? projResB.maxPoint : projResA.minPoint;

		}
		else if (minB <= maxA && minB >= minA)
		{
			result.overlap = maxA - minB;
			result.point = testNormal.isA ? projResB.minPoint : projResA.maxPoint;
			result.normal = testNormal.n * -1.0f;
		}

		return result;
	}

	// If colliding, sets collision point and normal and returns true
	bool CollisionTest(CCollider* ColliderA, CCollider* ColliderB, FVector3& point, FVector3& normal)
	{
		FOverlap minOverlap;
		minOverlap.overlap = 9999999.0f;

		// testing against up and right axii of each collider
		FTestNormal testNormals[] =
		{
			FTestNormal(ColliderA->GetOwner()->GetTransform()->GetUp(), true), FTestNormal(ColliderA->GetOwner()->GetTransform()->GetRight(), true),
			FTestNormal(ColliderB->GetOwner()->GetTransform()->GetUp(), false), FTestNormal(ColliderB->GetOwner()->GetTransform()->GetRight(), false)
		};

		for (const FTestNormal& testNormal : testNormals)
		{
			FOverlap overlap = GetOverlap(ColliderA, ColliderB, testNormal);

			if (overlap.overlap < 0.0f)
			{
				return false; // found a separating axis!
			}

			// keep track of min overlap to get collision point
			if (overlap.overlap < minOverlap.overlap)
			{
				minOverlap = overlap;
			}
		}

		if (minOverlap.isEdgeEdge)
		{
			// when edges collide perfectly, find 'middle' of overlap along axis perpendicular to collision normal

			normal = minOverlap.normal;
			FVector3 start = minOverlap.point.Project(normal); // start is collision point along normal

			// to find how much 'other axis' we need to add to start, find overlap along that axis first and then calculate middle
			FVector3 otherAxis = normal.Cross(FVector3::Forward());

			float minA, maxA, minB, maxB;
			FProjResult projResA, projResB;
			projResA = GetProj(ColliderA, otherAxis, minA, maxA);
			projResB = GetProj(ColliderB, otherAxis, minB, maxB);

			float otherLen = 0.0f;
			float otherOverlap = 0.0f;
			if (minA <= maxB && minA >= minB)
			{
				otherLen = minA;
				otherOverlap = fminf(maxB, maxA) - minA;
			}
			else if (minB <= maxA && minB >= minA)
			{
				otherLen = minB;
				otherOverlap = fminf(maxA, maxB) - minB;
			}

			otherLen += (otherOverlap * 0.5f);
			point = start + (otherAxis * otherLen);
		}
		else
		{
			normal = minOverlap.normal;
			point = minOverlap.point;
		}

		return true;
	}

	void CPhysics::Update()
	{
		for (CCollider* Collider: Colliders)
		{
			Collider->UpdatePoints();
		}

		// do each collider/collider check
		IColliderList::iterator iterA = Colliders.begin();
		while (iterA != Colliders.end())
		{
			IColliderList::iterator iterB = iterA;
			++iterB;
			while (iterB != Colliders.end())
			{
				CCollider* ColliderA = *iterA;
				CCollider* ColliderB = *iterB;

				FVector3 point;
				FVector3 normal;
				bool isColliding = CollisionTest(ColliderA, ColliderB, point, normal);

				// have to add/remove from each collider's own map
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

				++iterB;
			}

			++iterA;
		}

		// send collision for each map entry
		ICollisionMap::iterator iter = CollisionMap.begin();
		while (iter != CollisionMap.end())
		{
			CCollider* Collider = iter->first;
			ICollidersCollisions& collisions = iter->second;
			for (ICollidersCollisions::iterator iter2 = collisions.begin(); iter2 != collisions.end(); ++iter2)
			{
				Collider->OnCollision(iter2->second);
			}

			++iter;
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

		CollisionMap[key][collider] = FCollision(collider, point, normal);
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