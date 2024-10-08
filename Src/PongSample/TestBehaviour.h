#ifndef PKENGINE_PONGGAME_TESTBEHAVIOUR_H
#define PKENGINE_PONGGAME_TESTBEHAVIOUR_H

#include <Game/PKBehaviour.h>
#include <EngineComponents/PKPhysicsComponents.h>

namespace pkengine
{
	class CTestBehaviour : public CCollisionHandler
	{
	public:
		CTestBehaviour(CGameObject* InOwner) :
			CCollisionHandler(InOwner),
			DebugTransform(nullptr),
			DebugTransform2(nullptr),
			DebugMesh(nullptr),
			isColliding(false)
		{};

		virtual void OnCollision(const FCollision& collision) override;

		FTransform* DebugTransform;
		FTransform* DebugTransform2;
		class CMeshComponent* DebugMesh;

	protected:
		virtual void Update() override;
		bool isColliding;
	};
}

#endif // !PKENGINE_PONGGAME_TESTBEHAVIOUR_H
