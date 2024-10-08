#include <Systems/PKPhysics.h>

#include <EngineComponents/PKPhysicsComponents.h>
#include <Game/PKGameObject.h>

namespace pkengine
{
#define MAX_COLLIDERS 100

	CPhysics::IColliderList CPhysics::Colliders = CPhysics::IColliderList();
	CPhysics::ICollisionMap CPhysics::CollisionMap = CPhysics::ICollisionMap();
	unsigned int CPhysics::NumColliders = 0;

	/*
	void SATtest(const Vector3f& axis, const vector<Vector3f>& ptSet, float& minAlong, float& maxAlong)
	{
		minAlong = HUGE, maxAlong = -HUGE;
		for (int i = 0; i < ptSet.size(); i++)
		{
			// just dot it to get the min/max along this axis.
			float dotVal = ptSet[i].dot(axis);
			if (dotVal < minAlong)  minAlong = dotVal;
			if (dotVal > maxAlong)  maxAlong = dotVal;
		}
	}

	// Shape1 and Shape2 must be CONVEX HULLS
	bool intersects(Shape shape1, Shape shape2)
	{
		// Get the normals for one of the shapes,
		for (int i = 0; i < shape1.normals.size(); i++)
		{
			float shape1Min, shape1Max, shape2Min, shape2Max;
			SATtest(normals[i], shape1.corners, shape1Min, shape1Max);
			SATtest(normals[i], shape2.corners, shape2Min, shape2Max);
			if (!overlaps(shape1Min, shape1Max, shape2Min, shape2Max))
			{
				return 0; // NO INTERSECTION
			}

			// otherwise, go on with the next test
		}

		// TEST SHAPE2.normals as well

		// if overlap occurred in ALL AXES, then they do intersect
		return 1;
	}

	bool overlaps(float min1, float max1, float min2, float max2)
	{
		return isBetweenOrdered(min2, min1, max1) || isBetweenOrdered(min1, min2, max2);
	}

	inline bool isBetweenOrdered(float val, float lowerBound, float upperBound) {
		return lowerBound <= val && val <= upperBound;
	}

	*/

	struct FTestNormal
	{
		FVector3 n;
		bool isA;

		FTestNormal(const FVector3& inn, const bool inisA) :
			n(inn), isA(inisA) {}
	};

	FVector3 GetProj(const FVector3(&points)[4], const FVector3& axis, float& min, float& max, FVector3& minPoint, FVector3& maxPoint)
	{
		minPoint = points[0];
		min = minPoint.Dot(axis);
		max = min;

		for (const FVector3& point : points)
		{
			float dot = point.Dot(axis);
			if (dot < min)
			{
				min = dot;
				minPoint = point;
			}
			if (dot > max)
			{
				max = dot;
				maxPoint = point;
			}
		}

		return minPoint;
	}

	void GetOverlap(const FVector3(&pointsA)[4], const FVector3(&pointsB)[4], const FTestNormal& testNormal, FVector3& point, float& overlap, bool& flipN)
	{
		float minA, maxA, minB, maxB;
		FVector3 minPointA, minPointB, maxPointA, maxPointB;
		GetProj(pointsA, testNormal.n, minA, maxA, minPointA, maxPointA);
		GetProj(pointsB, testNormal.n, minB, maxB, minPointB, maxPointB);

		if (minA <= maxB && minA >= minB)
		{
			overlap = maxB - minA;
			point = minPointA;
		}
		else if (minB <= maxA && minB >= minA)
		{
			overlap = maxA - minB;
			flipN = true;
			point = minPointB;
		}
	}

	bool CollisionTest(const FVector3(&pointsA)[4], const FVector3(&pointsB)[4], const FTestNormal (&testNormals)[4], FVector3& point, FVector3& normal)
	{
		float minOverlap = 99999.0f;

		FVector3 testPoint;
		for (const FTestNormal& testNormal : testNormals)
		{
			float overlap = -1.0f;
			bool flipN = false;
			GetOverlap(pointsA, pointsB, testNormal, testPoint, overlap, flipN);

			if (overlap < 0.0f)
			{
				return false;
			}

			if (overlap < minOverlap)
			{
				minOverlap = overlap;
				normal = testNormal.n * (flipN ? -1.0f : 1.0f);
				point = testPoint;
			}
		}

		return true;
	}

	void CPhysics::Update()
	{
		for (CCollider* Collider: Colliders)
		{
			Collider->UpdatePoints();
		}

		for (CCollider* ColliderA : Colliders)
		{
			FTestNormal testNormals[] =
			{
				FTestNormal(ColliderA->GetOwner()->GetTransform()->GetUp(), true), FTestNormal(ColliderA->GetOwner()->GetTransform()->GetRight(), true),
				FTestNormal(FVector3(), false), FTestNormal(FVector3(), false)
			};

			for (CCollider* ColliderB : Colliders)
			{
				if (ColliderA == ColliderB) continue;

				testNormals[2].n = ColliderB->GetOwner()->GetTransform()->GetUp();
				testNormals[3].n = ColliderB->GetOwner()->GetTransform()->GetRight();

				FVector3 point;
				FVector3 normal;
				bool isColliding = CollisionTest(ColliderA->GetPoints(), ColliderB->GetPoints(), testNormals, point, normal);

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