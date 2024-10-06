#ifndef PKENGINE_PONGGAME_TESTBEHAVIOUR_H
#define PKENGINE_PONGGAME_TESTBEHAVIOUR_H

#include <Game/PKBehaviour.h>

namespace pkengine
{
	class CTestBehaviour : public CBehaviour
	{
	public:
		CTestBehaviour(CGameObject* InOwner) : CBehaviour(InOwner) {};

	protected:

		virtual void Update() override;
	};
}

#endif // !PKENGINE_PONGGAME_TESTBEHAVIOUR_H
