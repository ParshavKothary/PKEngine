#include <PongGame.h>
#include <MovementBehaviour.h>
#include <TestBehaviour.h>
#include <Core/PKEngine.h>
#include <Core/PKCommon.h>

namespace pkengine
{
	void CPongGame::Setup()
	{
        CGameObject* NewGameObj;

        NewGameObj = Engine->CreateGameObject<CGameObject>("TestTriangle");
        NewGameObj->AddMesh(EMeshType::Quad, FVector3(0.7f, 0.1f, 0.1f));
        NewGameObj->GetTransform()->SetScale(FVector3(0.2f, 0.4f, 1.0f));
        NewGameObj->AddBehaviour<CMovementBehaviour>();
        NewGameObj->AddBehaviour<CTestBehaviour>();

        NewGameObj = Engine->CreateGameObject<CGameObject>("TestTriangle2");
        NewGameObj->GetTransform()->SetScale(FVector3(0.2f, 0.2f, 1.0f));
        NewGameObj->GetTransform()->SetPosition(FVector3(0.2f, 0.5f, 0.0f));
        NewGameObj->AddMesh(EMeshType::Quad, FVector3(0.1f, 0.1f, 0.7f));
	}
}