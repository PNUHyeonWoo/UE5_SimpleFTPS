// Fill out your copyright notice in the Description page of Project Settings.


#include "Controller/SPEnemySoldierAIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"

ASPEnemySoldierAIController::ASPEnemySoldierAIController()
{
	static ConstructorHelpers::FObjectFinder<UBehaviorTree> BTAssetRef(TEXT("/Script/AIModule.BehaviorTree'/Game/AI/SPEnemySoldierBT.SPEnemySoldierBT'"));
	if (BTAssetRef.Object)
	{
		BTRef = BTAssetRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UBlackboardData> BBAssetRef(TEXT("/Script/AIModule.BlackboardData'/Game/AI/SPEnemySoldierBB.SPEnemySoldierBB'"));
	if (BBAssetRef.Object)
	{
		BBRef = BBAssetRef.Object;
	}
}

void ASPEnemySoldierAIController::RunBT()
{
	UBlackboardComponent* BBComp = Blackboard.Get();
	if (UseBlackboard(BBRef.Get(), BBComp))
	{
		RunBehaviorTree(BTRef.Get());
	}
}

void ASPEnemySoldierAIController::StopBT()
{
	UBehaviorTreeComponent* BTComp = Cast<UBehaviorTreeComponent>(BrainComponent);

	if (BTComp)
	{
		BTComp->StopTree();
	}
}

void ASPEnemySoldierAIController::BeginPlay()
{
	Super::BeginPlay();

	RunBT();

	UBlackboardComponent* BBComp = Blackboard.Get();
	BBComp->SetValueAsBool(TEXT("CanSeeTarget"), false);
	BBComp->SetValueAsObject(TEXT("Target"), UGameplayStatics::GetPlayerPawn(GetWorld(), 0));

	SetFocus(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
}
