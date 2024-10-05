#include <Game/PKBehaviour.h>
#include <Core/PKBase.h>

namespace pkengine
{
	CPKBehaviour_Internal::CPKBehaviour_Internal(CGameObject* InOwner)
	{
		assert(InOwner != nullptr);
		Owner = InOwner;
	}
}