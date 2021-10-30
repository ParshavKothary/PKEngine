#ifndef PKENGINE_MESHCOMPONENT_H
#define PKENGINE_MESHCOMPONENT_H

#include <Core/PKBase.h>
#include <Game/PKBehaviour.h>

namespace pkengine
{
	class CRenderer;

	class CMeshComponent : public CPKBehaviour
	{
		friend CRenderer;

	public:
		CMeshComponent(CGameObject* InOwner) : CPKBehaviour(InOwner)
		{
			RendererIndex = -1;
		}

		inline void SetColor(const FVector3& InColor) { Color = InColor; }
		inline FVector3 GetColor() const { return Color; }

	private:

		FVector3 Color;

		unsigned int RendererIndex;

		static const unsigned int NumVertices = 6;
		static const std::array<FVector3, NumVertices> BaseMeshVertices;
	};
}

#endif // !PKENGINE_MESHCOMPONENT_H
