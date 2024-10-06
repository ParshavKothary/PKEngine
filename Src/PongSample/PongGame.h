#ifndef PKENGINE_PONGGAME_PONGGAME_H
#define PKENGINE_PONGGAME_PONGGAME_H

#include <Game/PKGame.h>

namespace pkengine
{
	class CPKEngine;

	class CPongGame : public CGame
	{
	public:

		CPongGame(CPKEngine* EngineContext) : CGame(EngineContext) { }

	protected:

		void Setup() override;
	};
}

#endif // !PKENGINE_PONGGAME_PONGGAME_H