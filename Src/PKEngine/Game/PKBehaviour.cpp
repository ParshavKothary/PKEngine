#include <Game/PKBehaviour.h>
#include <Core/PKBase.h>

namespace pkengine
{
	CBehaviour::CBehaviour(CGameObject* InOwner)
	{
		assert(InOwner != nullptr);
		Owner = InOwner;
	}
}