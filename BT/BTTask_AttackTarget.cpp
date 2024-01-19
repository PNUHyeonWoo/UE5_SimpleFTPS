// Fill out your copyright notice in the Description page of Project Settings.


#include "BT/BTTask_AttackTarget.h"
#include "AIController.h"
#include "Interface/SPAIInterface.h"

UBTTask_AttackTarget::UBTTask_AttackTarget()
{
	bNotifyTick = true;
}

EBTNodeResult::Type UBTTask_AttackTarget::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	ISPAIInterface* AIInterface = Cast<ISPAIInterface>(OwnerComp.GetAIOwner()->GetPawn());
	if (AIInterface)
	{
		AIInterface->SetViewModeAttacking();
	}

	AttackCoolTimeRemaining = AttackCoolTime;

	return EBTNodeResult::InProgress;
}

void UBTTask_AttackTarget::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	AttackCoolTimeRemaining -= DeltaSeconds;

	if (AttackCoolTimeRemaining <= 0.0f)
	{
		ISPAIInterface* AIInterface = Cast<ISPAIInterface>(OwnerComp.GetAIOwner()->GetPawn());
		if (AIInterface)
		{
			AIInterface->ShotFromAI();
		}

		AttackCoolTimeRemaining = AttackCoolTime;
	}

}
