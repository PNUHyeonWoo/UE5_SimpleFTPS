// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "SPEnemySoldierAIController.generated.h"

/**
 * 
 */
UCLASS()
class SIMPLEFTPS_API ASPEnemySoldierAIController : public AAIController
{
	GENERATED_BODY()

public:
	ASPEnemySoldierAIController();

	void RunBT();
	void StopBT();

	virtual void BeginPlay() override;

private:
	UPROPERTY()
	TObjectPtr<class UBehaviorTree> BTRef;
	UPROPERTY()
	TObjectPtr<class UBlackboardData> BBRef;
	
	
};
