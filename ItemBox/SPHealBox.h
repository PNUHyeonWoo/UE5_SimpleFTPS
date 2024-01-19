// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemBox/SPItemBox.h"
#include "SPHealBox.generated.h"

/**
 * 
 */
UCLASS()
class SIMPLEFTPS_API ASPHealBox : public ASPItemBox
{
	GENERATED_BODY()

public:
	ASPHealBox();

protected:
	virtual bool GiveItem(AActor* OtherActor) override;

protected:
	UPROPERTY(EditAnywhere, Category = Stat)
	float HealAmount;
	
};
