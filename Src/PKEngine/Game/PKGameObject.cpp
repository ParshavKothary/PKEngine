#include <Game/PKGameObject.h>
#include <Core/PKEngine.h>
#include <Game/PKBehaviour.h>
#include <Game/PKGame.h>
#include <EngineComponents/PKMeshComponent.h>
#include <EngineComponents/PKPhysicsComponents.h>
#include <Systems/PKRendering.h>
#include <Systems/PKPhysics.h>

namespace pkengine
{
	CGameObject::CGameObject(CGame* GameContext)
	{
		assert(GameContext != nullptr);
		Game = GameContext;
		Behaviours = containers::umap<size_t, CBehaviour*>();
		Transform = new FTransform();
		MeshComponent = nullptr;
		Collider = nullptr;
	}

	CGameObject::~CGameObject()
	{
		if (MeshComponent != nullptr)
		{
			CRenderer::UnregisterMesh(MeshComponent);
		}

		if (Collider != nullptr)
		{
			CPhysics::UnregisterCollider(Collider);
		}

		for (IBehavioursIterator it = Behaviours.begin(); it != Behaviours.end();)
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

		MeshComponent = AddBehaviourInternal<CMeshComponent>();
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

		Collider = AddBehaviourInternal<CCollider>();
		if (Collider != nullptr)
		{
			Collider->SetSizeAndOffset(size, offset);
		}

		return Collider;
	}

	void CGameObject::Start()
	{
		for (IBehavioursIterator it = Behaviours.begin(); it != Behaviours.end(); ++it)
		{
			CBehaviour* pBehaviour = it->second;
			pBehaviour->Start();
		}
	}

	void CGameObject::Update()
	{
		for (IBehavioursIterator it = Behaviours.begin(); it != Behaviours.end(); ++it)
		{
			CBehaviour* pBehaviour = it->second;
			pBehaviour->Update();
		}
	}
}