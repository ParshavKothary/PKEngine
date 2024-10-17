#include "Wall.h"

namespace pkengine
{
	namespace ponggame
	{
		void CWall::Setup()
		{
			CGameObject::Setup();

			AddMeshComponent(EMeshType::Quad, FVector3(0.1f, 0.1f, 0.1f));
			AddCollider();
		}
	}
}