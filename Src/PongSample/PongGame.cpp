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

        NewGameObj = CreateGameObject<CGameObject>("TestTriangle");
        CMeshComponent* mesh = NewGameObj->AddMeshComponent(EMeshType::Quad, FVector3(0.7f, 0.1f, 0.1f));
        NewGameObj->GetTransform()->SetScale(FVector3(2.0f, 4.0f, 1.0f));
        NewGameObj->AddBehaviour<CMovementBehaviour>();
        CTestBehaviour* testB = NewGameObj->AddBehaviour<CTestBehaviour>();
        NewGameObj->AddCollider(FVector3::One(), FVector3());

        NewGameObj = CreateGameObject<CGameObject>("TestTriangle2");
        NewGameObj->GetTransform()->SetScale(FVector3(2.0f, 2.0f, 1.0f));
        NewGameObj->GetTransform()->SetPosition(FVector3(2.0f, 5.0f, 0.0f));
        NewGameObj->AddMeshComponent(EMeshType::Quad, FVector3(0.1f, 0.1f, 0.7f));
        NewGameObj->AddCollider(FVector3::One(), FVector3());

        CGameObject* DebugObj = CreateGameObject<CGameObject>("DebugObj");
        DebugObj->AddMeshComponent(EMeshType::Quad, FVector3(1.0f, 1.0f, 1.0f));
        DebugObj->GetTransform()->SetScale(FVector3(0.2f, 0.2f, 1.0f));

        CGameObject* DebugObj2 = CreateGameObject<CGameObject>("DebugObj2");
        DebugObj2->AddMeshComponent(EMeshType::Quad, FVector3(1.0f, 1.0f, 1.0f));
        DebugObj2->GetTransform()->SetScale(FVector3(0.1f, 1.0f, 1.0f));

        testB->DebugTransform = DebugObj->GetTransform();
        testB->DebugTransform2 = DebugObj2->GetTransform();
        testB->DebugMesh = mesh;


        NewGameObj = CreateGameObject<CGameObject>("TestTriangle3");
        NewGameObj->AddMeshComponent(EMeshType::Quad, FVector3(0.4f, 0.0f, 0.0f));
        NewGameObj->GetTransform()->SetPosition(FVector3(3.0f, 3.0f));


        NewGameObj = CreateGameObject<CGameObject>("TestTriangle3");
        NewGameObj->AddMeshComponent(EMeshType::Quad, FVector3(0.0f, 0.4f, 0.0f));
        NewGameObj->GetTransform()->SetPosition(FVector3(-3.0f, -3.0f));
	}
}