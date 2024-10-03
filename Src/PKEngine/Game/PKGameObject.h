#ifndef PKENGINE_PKGAMEOBJECT_H
#define PKENGINE_PKGAMEOBJECT_H

#include <Core/PKBase.h>

namespace pkengine
{
	class CMeshComponent;
	class CPKBehaviour;
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

		CMeshComponent* AddMesh(EMeshType MeshType, const FVector3& Color);

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

		containers::umap<size_t, CPKBehaviour*> Behaviours;
		typedef containers::umap<size_t, CPKBehaviour*>::iterator BehavioursIterator;
	};

	template<typename T>
	inline T* CGameObject::AddBehaviour()
	{
		static_assert(std::is_base_of<CPKBehaviour, T>()); // T needs to derive from CPKBehaviour!

		size_t typehash = typeid(T).hash_code();
		if (Behaviours.find(typehash) != Behaviours.end())
		{
			std::cout << "Error: Trying to multiple of same behaviour type to GameObject" << std::endl;
			return nullptr;
		}

		T* NewBehaviour = new T(this);
		Behaviours.insert({ typehash, static_cast<CPKBehaviour*>(NewBehaviour) });
		return NewBehaviour;
	}

	template<typename T>
	inline T* CGameObject::GetBehaviour()
	{
		static_assert(std::is_base_of<CPKBehaviour, T>()); // T needs to derive from CPKBehaviour!

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
