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

		CMeshComponent* AddMesh(EMeshType MeshType);

		template<typename T>
		T* AddBehaviour();

	protected:

		virtual void Setup() {}

		FTransform* Transform;

	private:

		void RegisterBehaviour(CPKBehaviour* Behaviour);

		CPKGame* Game;
		char Name[32];
		CMeshComponent* MeshComponent;

		std::list<CPKBehaviour*> Behaviours;
	};

	template<typename T>
	inline T* CGameObject::AddBehaviour()
	{
		static_assert(std::is_base_of<CPKBehaviour, T>()); // T needs to derive from CPKBehaviour!

		T* NewBehaviour = new T(this);
		RegisterBehaviour(NewBehaviour);
		return NewBehaviour;
	}
}

#endif // !PKENGINE_PKGAMEOBJECT_H
