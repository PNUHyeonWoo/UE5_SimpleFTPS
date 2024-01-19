// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "SPGunData.generated.h"

/**
 * 
 */
UCLASS()
class SIMPLEFTPS_API USPGunData : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	USPGunData();

	virtual FPrimaryAssetId GetPrimaryAssetId() const override;

public:
	UPROPERTY(EditAnywhere, Category = Gun)
	TSoftObjectPtr<USkeletalMesh> GunMesh;

	UPROPERTY(EditAnywhere, Category = Gun)
	TSoftObjectPtr<UStaticMesh> MagazineMesh;

	UPROPERTY(EditAnywhere, Category = Gun)
	float GunDamage;

	UPROPERTY(EditAnywhere, Category = Gun)
	float ShootingCoolTime;

	UPROPERTY(EditAnywhere, Category = Gun)
	int16 Capacity;

};
