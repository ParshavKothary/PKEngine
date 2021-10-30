#ifndef PKENGINE_PONGGAME_PONGGAME_H
#define PKENGINE_PONGGAME_PONGGAME_H

#include <Game/PKGame.h>

namespace pkengine
{
	class CPKEngine;

	class CPongGame : public CPKGame
	{
	public:

		CPongGame(CPKEngine* EngineContext) : CPKGame(EngineContext) { }

	protected:

		void Setup() override;
	};
}

#endif // !PKENGINE_PONGGAME_PONGGAME_H