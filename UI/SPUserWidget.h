// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SPUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class SIMPLEFTPS_API USPUserWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	USPUserWidget(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void NativeConstruct() override;

public:
	void SetMaxHP(float Value);
	void SetHP(float Value);
	void SetMaxAmmo(int Value);
	void SetCurrentAmmo(int Value);
	

protected:
	UPROPERTY()
	TObjectPtr<class UProgressBar> HPProgressBar;

	UPROPERTY()
	TObjectPtr<class UTextBlock> MaxAmmo;

	UPROPERTY()
	TObjectPtr<class UTextBlock> CurrentAmmo;

protected:
	UPROPERTY(VisibleAnywhere, Category = Stat)
	float MaxHP;

	
};
