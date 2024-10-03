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
		Behaviours = containers::umap<size_t, CPKBehaviour*>();
		Transform = new FTransform();
		MeshComponent = nullptr;
	}

	CGameObject::~CGameObject()
	{
		for (BehavioursIterator it = Behaviours.begin(); it != Behaviours.end();)
		{
			delete it->second;
			it = Behaviours.erase(it);
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

	void CGameObject::Update()
	{
		for (BehavioursIterator it = Behaviours.begin(); it != Behaviours.end(); ++it)
		{
			CPKBehaviour* pBehaviour = it->second;
			pBehaviour->Update();
		}
	}
}