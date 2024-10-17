#pragma once
#ifndef PKENGINE_PONGGAME_CPADDLE_H
#define PKENGINE_PONGGAME_CPADDLE_H

#include <Core/PKBase.h>
#include <Game/PKGameObject.h>

namespace pkengine
{
	namespace ponggame
	{
		class CBallMove;

		class CPaddle : public CGameObject
		{

		protected:
			EKeyCode upKey;
			EKeyCode downKey;
			EKeyCode shootKey;
			FVector3 shootDir;

			float upDir;
			CBallMove* Ball;

			void UpdateMove();
			void UpdateShoot();

		public:
			CPaddle(CGame* GameContext):
				CGameObject(GameContext)
			{
				upKey = EKeyCode::KeyCode_W;
				downKey = EKeyCode::KeyCode_S;
				shootKey = EKeyCode::KeyCode_D;
				upDir = 0.0f;
				shootDir = FVector3::Right();
				Ball = nullptr;
			}

			virtual void Setup() override;
			virtual void Update() override;

			inline float GetUpDir() const { return upDir; }

			void SetPlayer(unsigned int player);
			void GiveBall(CBallMove* inBall);
			void ShootBall();
		};
	}
}

#endif