#include <Game/PKGameObject.h>
#include <Core/PKEngine.h>
#include <Game/PKBehaviour.h>
#include <Game/PKGame.h>
#include <EngineComponents/PKMeshComponent.h>
#include <EngineComponents/PKPhysicsComponents.h>
#include <Systems/PKRendering.h>

namespace pkengine
{
	CGameObject::CGameObject(CGame* GameContext)
	{
		assert(GameContext != nullptr);
		Game = GameContext;
		Behaviours = containers::umap<size_t, CBehaviour*>();
		Transform = new FTransform();
		MeshComponent = nullptr;
	}

	CGameObject::~CGameObject()
	{
		if (MeshComponent != nullptr)
		{
			CRenderer::UnregisterMesh(MeshComponent);
		}

		for (BehavioursIterator it = Behaviours.begin(); it != Behaviours.end();)
		{
			delete it->second;
			it = Behaviours.erase(it);
		}

		delete Transform;
	}

	CMeshComponent* CGameObject::AddMeshComponent(EMeshType MeshType, const FVector3& Color)
	{
		if (MeshComponent != nullptr)
		{
			std::cout << "Error: Trying to add multiple meshes to same GameObject" << std::endl;
			return nullptr;
		}

		MeshComponent = AddBehaviour<CMeshComponent>();
		if (MeshComponent != nullptr)
		{
			MeshComponent->SetColor(Color);
		}

		return MeshComponent;
	}

	CCollider* CGameObject::AddCollider(const FVector3& size, const FVector3& offset)
	{
		if (Collider != nullptr)
		{
			std::cout << "Error: Trying to add multiple colliders to same GameObject" << std::endl;
			return nullptr;
		}

		Collider = AddBehaviour<CCollider>();
		if (Collider != nullptr)
		{
			Collider->SetSizeAndOffset(size, offset);
		}

		return Collider;
	}

	void CGameObject::Start()
	{
		for (BehavioursIterator it = Behaviours.begin(); it != Behaviours.end(); ++it)
		{
			CBehaviour* pBehaviour = it->second;
			pBehaviour->Start();
		}
	}

	void CGameObject::Update()
	{
		for (BehavioursIterator it = Behaviours.begin(); it != Behaviours.end(); ++it)
		{
			CBehaviour* pBehaviour = it->second;
			pBehaviour->Update();
		}
	}
}