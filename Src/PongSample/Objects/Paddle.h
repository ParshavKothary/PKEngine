#pragma once
#ifndef PKENGINE_PONGGAME_CPADDLE_H
#define PKENGINE_PONGGAME_CPADDLE_H

#include <Core/PKBase.h>
#include <Game/PKGameObject.h>

namespace pkengine
{
	namespace ponggame
	{
		class CPaddle : public CGameObject
		{

		protected:
			EKeyCode upKey;
			EKeyCode downKey;

			float upDir;

		public:
			CPaddle(CGame* GameContext):
				CGameObject(GameContext)
			{
				upKey = EKeyCode::KeyCode_W;
				downKey = EKeyCode::KeyCode_S;
				upDir = 0.0f;
			}

			virtual void Setup() override;
			virtual void Update() override;

			void SetKeys(EKeyCode up, EKeyCode down)
			{
				upKey = up;
				downKey = down;
			}

			inline float GetUpDir() const { return upDir; }
		};
	}
}

#endif