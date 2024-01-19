// Fill out your copyright notice in the Description page of Project Settings.


#include "Gun/SPGunData.h"

USPGunData::USPGunData() 
{
	GunDamage = 50.0f;
	ShootingCoolTime = 0.2f;
	Capacity = 30;
}

FPrimaryAssetId USPGunData::GetPrimaryAssetId() const
{
	return FPrimaryAssetId("SPGunData",GetFName());
}
