// Fill out your copyright notice in the Description page of Project Settings.


#include "BT/BTTask_StartMoving.h"
#include "AIController.h"
#include "Interface/SPAIInterface.h"

EBTNodeResult::Type UBTTask_StartMoving::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	ISPAIInterface* AIInterface = Cast<ISPAIInterface>(OwnerComp.GetAIOwner()->GetPawn());
	if (AIInterface) 
	{
		AIInterface->SetViewModeMoving();
	}

	return EBTNodeResult::Succeeded;
}
