#pragma once
#ifndef PKENGINE_PONGGAME_CBALL_H
#define PKENGINE_PONGGAME_CBALL_H

#include <Core/PKBase.h>
#include <Game/PKGameObject.h>

namespace pkengine
{
	namespace ponggame
	{
		class CBall : public CGameObject
		{
		public:
			CBall(CGame* GameContext) : CGameObject(GameContext) {}
			virtual void Setup() override;
		};
	}
}

#endif