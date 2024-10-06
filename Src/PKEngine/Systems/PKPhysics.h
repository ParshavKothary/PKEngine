#ifndef PKENGINE_PKPHYSICS_H
#define PKENGINE_PKPHYSICS_H

#include <Core/PKBase.h>

namespace pkengine
{
	class CCollider;

	class CPhysics
	{
	public:

		static void Update();
		static void PostUpdate();
		static bool RegisterCollider(CCollider* Collider);
		static void UnregisterCollider(CCollider* Collider);

	private:

		static void AddToCollisionMap(CCollider* key, CCollider* collider, const FVector3& point, const FVector3& normal);
		static void RemoveFromCollisionMap(CCollider* key, CCollider* collider);

		typedef containers::uset<CCollider*> IColliderList;
		typedef containers::map<CCollider*, FCollision> ICollidersCollisions;
		typedef containers::map<CCollider*, ICollidersCollisions> ICollisionMap;

		static unsigned int NumColliders;
		static IColliderList Colliders;
		static ICollisionMap CollisionMap;
	};
}

#endif // !PKENGINE_PKPHYSICS_H
