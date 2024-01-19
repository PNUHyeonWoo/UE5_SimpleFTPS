// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BTService_SetCanSeeTarget.generated.h"

/**
 * 
 */
UCLASS()
class SIMPLEFTPS_API UBTService_SetCanSeeTarget : public UBTService
{
	GENERATED_BODY()

public:
	UBTService_SetCanSeeTarget();

protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp,uint8* NodeMemory,float DeltaSecond) override;

	
};
