#include <Game/PKBehaviour.h>
#include <Core/PKBase.h>

namespace pkengine
{
	CPKBehaviour::CPKBehaviour(CGameObject* InOwner)
	{
		assert(InOwner != nullptr);
		Owner = InOwner;
	}
}