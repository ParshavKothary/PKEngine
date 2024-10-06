#include <Game/PKBehaviour.h>
#include <Core/PKBase.h>

namespace pkengine
{
	CBehaviour_Internal::CBehaviour_Internal(CGameObject* InOwner)
	{
		assert(InOwner != nullptr);
		Owner = InOwner;
	}
}