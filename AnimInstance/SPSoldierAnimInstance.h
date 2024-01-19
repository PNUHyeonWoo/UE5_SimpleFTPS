// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "SPSoldierAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class SIMPLEFTPS_API USPSoldierAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	USPSoldierAnimInstance();
protected:
	virtual void NativeUpdateAnimation(float DeltaTime) override;
	UFUNCTION(BlueprintCallable, Category = Soldier)
	void InsertMagazine();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Character)
	float Speed;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Character)
	float UpperBodyWeight;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Character)
	float UpperBodySmoothWeight;

	const float SmoothWeightAcceleration = 3.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Character)
	float ControlPitch;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Character)
	float RelativeMovingAngle;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Character)
	uint8 bIsTryingToReload : 1;
	
};
