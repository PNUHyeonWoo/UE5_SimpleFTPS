// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "SPAIInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class USPAIInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class SIMPLEFTPS_API ISPAIInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void SetViewModeMoving() = 0;
	virtual void SetViewModeAttacking() = 0;
	virtual void ShotFromAI() = 0;
};
