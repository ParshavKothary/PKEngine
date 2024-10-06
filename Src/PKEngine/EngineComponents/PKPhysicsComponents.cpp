#include <EngineComponents/PKPhysicsComponents.h>

namespace pkengine
{
	void CCollider::SetSizeAndOffset(const FVector3& size, const FVector3& offset)
	{
		max = (size * 0.5f) + offset;
		min = (size * -0.5f) + offset;
	}

	bool CCollider::CheckConstruct()
	{
		return true;
	}

	void CCollisionHandler::OnCollision()
	{

	}
}