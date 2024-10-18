#ifndef PKENGINE_PKPHYSICS_H
#define PKENGINE_PKPHYSICS_H

#include <Core/PKBase.h>

namespace pkengine
{
	class CCollider;

	class CPhysics
	{
	public:

		static void Init();
		static void CleanUp();
		static void Update();
		static bool RegisterCollider(CCollider* Collider);
		static void UnregisterCollider(CCollider* Collider);

	private:

		enum EColStage
		{
			Enter,
			Stay,
			Exit
		};

		struct FColEntry
		{
			EColStage stage;
			FCollision col;

			FColEntry() : stage(EColStage::Enter), col() {}
		};

		typedef containers::uset<CCollider*> IColliderList;
		typedef containers::map<CCollider*, FColEntry> ICollidersCollisions;
		typedef containers::map<CCollider*, ICollidersCollisions> ICollisionMap;

		void AddToCollisionMap(CCollider* key, CCollider* collider, const FVector3& point, const FVector3& normal);
		void RemoveFromCollisionMap(CCollider* key, CCollider* collider);

		void UpdateInternal();
		bool RegisterColliderInternal(CCollider* Collider);
		void UnregisterColliderInternal(CCollider* Collider);

		CPhysics() :
			NumColliders(0)
		{}

		static CPhysics* Instance;

		unsigned int NumColliders;
		IColliderList Colliders;
		ICollisionMap CollisionMap;
	};
}

#endif // !PKENGINE_PKPHYSICS_H
