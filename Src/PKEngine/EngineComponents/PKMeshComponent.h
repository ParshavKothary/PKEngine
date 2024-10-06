#ifndef PKENGINE_PKMESHCOMPONENT_H
#define PKENGINE_PKMESHCOMPONENT_H

#include <Core/PKBase.h>
#include <Game/PKBehaviour.h>

namespace pkengine
{
	class CRenderer;

	class CMeshComponent : public CBehaviour_Internal
	{
		friend CRenderer;

	public:
		CMeshComponent(CGameObject* InOwner) : CBehaviour_Internal(InOwner)
		{
			RendererIndex = -1;
		}

		inline void SetColor(const FVector3& InColor) { Color = InColor; }
		inline FVector3 GetColor() const { return Color; }

		virtual bool CheckConstruct() override;

	private:

		FVector3 Color;

		unsigned int RendererIndex;

		static const unsigned int NumVertices = 6;
		static const std::array<FVector3, NumVertices> BaseMeshVertices;
	};
}

#endif // !PKENGINE_PKMESHCOMPONENT_H
