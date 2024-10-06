#ifndef PKENGINE_PKGAMEOBJECT_H
#define PKENGINE_PKGAMEOBJECT_H

#include <Core/PKBase.h>

namespace pkengine
{
	class CBehaviour;
	class CBehaviour;
	class CCollider;
	class CCollisionHandler;
	class CMeshComponent;
	class CPKEngine;
	class CPKGame;

	class CGameObject
	{
		friend CPKEngine;

	public:

		CGameObject(CPKGame* GameContext);
		virtual ~CGameObject();
		
		inline CPKGame* GetGame() const { return Game; }

		inline const char* GetName() const { return Name; }

		inline FTransform* GetTransform() const { return Transform; }

		CMeshComponent* AddMeshComponent(EMeshType MeshType, const FVector3& Color);

		CCollider* AddCollider(const FVector3& size, const FVector3& offset);

		template<typename T>
		T* AddBehaviour();

		template<typename T>
		T* GetBehaviour();

		virtual void Update();

	protected:

		virtual void Setup() {}

		FTransform* Transform;

	private:

		CPKGame* Game;
		char Name[32];
		CMeshComponent* MeshComponent;
		CCollider* Collider;

		containers::umap<size_t, CBehaviour*> Behaviours;
		typedef containers::umap<size_t, CBehaviour*>::iterator BehavioursIterator;
	};

	template<typename T>
	T* CGameObject::AddBehaviour()
	{
		static_assert(std::is_base_of<CBehaviour, T>());

		size_t typehash = typeid(T).hash_code();
		if (Behaviours.find(typehash) != Behaviours.end())
		{
			std::cout << "Error: Trying to multiple of " << typeid(T).name() << " type to GameObject " << Name << std::endl;
			return nullptr;
		}

		T* NewBehaviour = new T(this);
		CBehaviour* BehaviourBase = static_cast<CBehaviour*>(NewBehaviour);
		if (BehaviourBase->CheckConstruct() == false)
		{
			delete NewBehaviour;
			return nullptr;
		}
		
		Behaviours.insert({ typehash, static_cast<CBehaviour*>(NewBehaviour) });
		
		return NewBehaviour;
	}

	template<typename T>
	T* CGameObject::GetBehaviour()
	{
		static_assert(std::is_base_of<CBehaviour, T>());

		size_t typehash = typeid(T).hash_code();
		BehavioursIterator it = Behaviours.find(typehash);
		if (it != Behaviours.end())
		{
			return dynamic_cast<T*>(it->second);
		}

		return nullptr;
	}
}

#endif // !PKENGINE_PKGAMEOBJECT_H
