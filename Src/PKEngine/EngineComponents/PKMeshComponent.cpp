#include <EngineComponents/PKMeshComponent.h>
#include <Systems/PKRendering.h>

namespace pkengine
{
    const std::array<FVector3, CMeshComponent::NumVertices> CMeshComponent::BaseMeshVertices
    {{
        FVector3(-0.5f, 0.5f, 0.0f),
        FVector3(-0.5f, -0.5f, 0.0f),
        FVector3(0.5f, -0.5f, 0.0f),
        FVector3(-0.5f, 0.5f, 0.0f),
        FVector3(0.5f, 0.5f, 0.0f),
        FVector3(0.5f, -0.5f, 0.0f)
    }};

    bool CMeshComponent::CheckConstruct()
    {
        return CRenderer::RegisterMesh(this);
    }
}