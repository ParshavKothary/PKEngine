#include <Game/PKBehaviour.h>
#include <Core/PKCommon.h>

namespace pkengine
{
	CPKBehaviour::CPKBehaviour(CGameObject* InOwner)
	{
		assert(InOwner != nullptr);
		Owner = InOwner;
	}
}