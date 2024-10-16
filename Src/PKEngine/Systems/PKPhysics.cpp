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
		union
		{
			FEdge minEdge;
			FVector3 minPoint;
		};

		union
		{
			FEdge maxEdge;
			FVector3 maxPoint;
		};

		bool isEdge;

		FProjResult() :
			minEdge(),
			maxEdge(),
			isEdge(false)
		{}

		FProjResult(const FProjResult& other)
		{
			isEdge = other.isEdge;

			if (isEdge)
			{
				minEdge = other.minEdge;
				maxEdge = other.maxEdge;
			}
			else
			{
				minPoint = other.minPoint;
				maxPoint = other.maxPoint;
			}
		}

		FProjResult& operator=(const FProjResult& other)
		{
			isEdge = other.isEdge;

			if (isEdge)
			{
				minEdge = other.minEdge;
				maxEdge = other.maxEdge;
			}
			else
			{
				minPoint = other.minPoint;
				maxPoint = other.maxPoint;
			}

			return *this;
		}
	};

	struct FOverlap
	{
		FVector3 point;
		FTestNormal normal;
		float overlap;
		bool isEdgeEdge;

		FOverlap() :
			point(),
			normal(FVector3(1.0f, 0.0f), false),
			overlap(-1.0f),
			isEdgeEdge(false) {}
	};

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
			if (dot <= min)
			{
				if (dot == min)
				{
					result.isEdge = true;
					result.minEdge.b = point;
				}
				else
				{
					min = dot;
					result.isEdge = false;
					result.minPoint = point;
				}
			}
			if (dot >= max)
			{
				if (dot == max)
				{
					result.isEdge = true;
					result.maxEdge.b = point;
				}
				else
				{
					max = dot;
					result.isEdge = false;
					result.maxPoint = point;
				}
			}
		}

		return result;
	}

	FOverlap GetOverlap(const CCollider* ColliderA, CCollider* ColliderB, const FTestNormal& testNormal)
	{
		FOverlap result;

		float minA, maxA, minB, maxB;
		FProjResult projResA, projResB;
		projResA = GetProj(ColliderA, testNormal.n, minA, maxA);
		projResB = GetProj(ColliderB, testNormal.n, minB, maxB);

		result.normal.n = testNormal.n;
		result.normal.isA = testNormal.isA;

		if (minA <= maxB && minA >= minB)
		{
			result.overlap = maxB - minA;
			result.point = testNormal.isA ? projResB.maxPoint : projResA.minPoint;

			result.isEdgeEdge = projResB.isEdge && projResA.isEdge;
		}
		else if (minB <= maxA && minB >= minA)
		{
			result.overlap = maxA - minB;
			result.point = testNormal.isA ? projResB.minPoint : projResA.maxPoint;
			result.normal.n = testNormal.n * -1.0f;

			result.isEdgeEdge = projResB.isEdge && projResA.isEdge;
		}

		return result;
	}

	bool CollisionTest(CCollider* ColliderA, CCollider* ColliderB, FVector3& point, FVector3& normal)
	{
		FOverlap minOverlap;
		minOverlap.overlap = 9999999.0f;

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

			if (overlap.overlap < minOverlap.overlap)
			{
				minOverlap = overlap;
			}
		}

		if (minOverlap.isEdgeEdge)
		{
			normal = minOverlap.normal.n;
			FVector3 start = minOverlap.point.Project(normal);
			FVector3 otherAxis = normal.Cross(FVector3::Forward());

			float otherLen = 1.0f;

			float minA, maxA, minB, maxB;
			FProjResult projResA, projResB;
			projResA = GetProj(ColliderA, otherAxis, minA, maxA);
			projResB = GetProj(ColliderB, otherAxis, minB, maxB);


			if (minA <= maxB && minA >= minB)
			{
				float diff = fminf(maxB, maxA) - minA;
				otherLen  = minA + (diff * 0.5f);
			}
			else if (minB <= maxA && minB >= minA)
			{
				float diff = fminf(maxA, maxB) - minB;
				otherLen  = minB + (diff * 0.5f);
			}

			point = start + (otherAxis * otherLen);
		}
		else
		{
			normal = minOverlap.normal.n;
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