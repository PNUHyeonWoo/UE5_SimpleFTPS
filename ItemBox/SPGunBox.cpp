// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemBox/SPGunBox.h"
#include "Interface/SPGunInterface.h"
#include "Gun/SPGunData.h"

ASPGunBox::ASPGunBox()
{
    static ConstructorHelpers::FObjectFinder<USPGunData> GunDataRef(TEXT("/Script/SimpleFTPS.SPGunData'/Game/Gun/AR1.AR1'"));

    if (GunDataRef.Object)
    {
        Gun = GunDataRef.Object;
    }
}

bool ASPGunBox::GiveItem(AActor* OtherActor)
{
    Super::GiveItem(OtherActor);

    ISPGunInterface* GunInteface = Cast<ISPGunInterface>(OtherActor);

    if (GunInteface)
    {
        if (GunInteface->GetGun() != Gun)
        {
            GunInteface->EquipGun(Gun);
            return true;
        }
    }

	return false;
}
