#include <Game/PKGameObject.h>
#include <Core/PKEngine.h>
#include <Game/PKBehaviour.h>
#include <Game/PKGame.h>
#include <EngineComponents/PKMeshComponent.h>
#include <Systems/PKRendering.h>

namespace pkengine
{
	CGameObject::CGameObject(CPKGame* GameContext)
	{
		assert(GameContext != nullptr);
		Game = GameContext;
		Behaviours = std::list<CPKBehaviour*>();
		Transform = new FTransform();
	}

	CGameObject::~CGameObject()
	{
		while (Behaviours.empty() == false)
		{
			delete Behaviours.front();
			Behaviours.pop_front();
		}

		if (MeshComponent != nullptr)
		{
			CRenderer::UnregisterMesh(MeshComponent);
		}

		delete Transform;
	}

	CMeshComponent* CGameObject::AddMesh(EMeshType MeshType, const FVector3& Color)
	{
		if (MeshComponent != nullptr)
		{
			std::cout << "Error: Trying to add multiple meshes to same GameObject" << std::endl;
			return nullptr;
		}

		MeshComponent = CRenderer::RegisterMesh(this);
		if (MeshComponent != nullptr)
		{
			MeshComponent->SetColor(Color);
		}

		return MeshComponent;
	}

	void CGameObject::RegisterBehaviour(CPKBehaviour* Behaviour)
	{
		Behaviours.push_back(Behaviour);
	}
}