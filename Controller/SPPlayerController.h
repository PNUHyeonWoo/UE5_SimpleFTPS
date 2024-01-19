// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "SPPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class SIMPLEFTPS_API ASPPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ASPPlayerController();

protected:
	virtual void BeginPlay() override;



protected:
	UPROPERTY(VisibleAnywhere, Category = UI)
	TSubclassOf<class USPUserWidget> SPUserWidgetBPClass;

	UPROPERTY(VisibleAnywhere, Category = UI)
	TObjectPtr<class USPUserWidget> SPUserWidget;


	
};
