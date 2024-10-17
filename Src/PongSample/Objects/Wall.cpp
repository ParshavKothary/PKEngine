#include "Wall.h"

namespace pkengine
{
	namespace ponggame
	{
		void CWall::Setup()
		{
			CGameObject::Setup();

			AddMeshComponent(EMeshType::Quad, FVector3(0.3f, 0.3f, 0.3f));
			AddCollider();
		}
	}
}