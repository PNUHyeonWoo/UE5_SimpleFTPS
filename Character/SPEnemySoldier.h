// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/SPSoldier.h"
#include "Interface/SPAIInterface.h"
#include "SPEnemySoldier.generated.h"

/**
 * 
 */
UCLASS()
class SIMPLEFTPS_API ASPEnemySoldier : public ASPSoldier, public ISPAIInterface
{
	GENERATED_BODY()

public:
	ASPEnemySoldier();

protected:
	virtual void BeginPlay() override;

public:
	virtual void SetViewModeMoving() override;
	virtual void SetViewModeAttacking() override;
	virtual void ShotFromAI() override;
	static int GetNumOfEnemySoldier();
	static void SetNumOfEnemySoldier(int Value);

protected:
	virtual void Tick(float deltaTime) override;
	virtual void SetDead() override;

protected:
	static int NumOfEnemySoldier;
	
};
