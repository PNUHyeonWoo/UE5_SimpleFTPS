// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemBox/SPItemBox.h"
#include "SPGunBox.generated.h"

/**
 * 
 */
UCLASS()
class SIMPLEFTPS_API ASPGunBox : public ASPItemBox
{
	GENERATED_BODY()

public:
	ASPGunBox();

protected:
	virtual bool GiveItem(AActor* OtherActor) override;

protected:
	UPROPERTY(EditAnywhere, Category = Gun)
	TObjectPtr<class USPGunData> Gun;
	
};
