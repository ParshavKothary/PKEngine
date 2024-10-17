#include "Ball.h"
#include <Behaviours/BallMove.h>

namespace pkengine
{
	namespace ponggame
	{
		void CBall::Setup()
		{
			CGameObject::Setup();

			AddMeshComponent(EMeshType::Quad, FVector3(0.8f, 0.2f, 0.2f));
			AddCollider();
			AddBehaviour<CBallMove>();
		}
	}
}