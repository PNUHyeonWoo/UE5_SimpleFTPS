// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "SPGunInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class USPGunInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class SIMPLEFTPS_API ISPGunInterface
{
	GENERATED_BODY()

public:
	virtual class USPGunData* GetGun() = 0;
	virtual void EquipGun(class USPGunData* GunData) = 0;
	virtual void Reload() = 0;
	virtual void RemoveMagazine() = 0;
	virtual void InsertMagazine() = 0;
};
