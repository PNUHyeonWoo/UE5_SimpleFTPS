// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemBox/SPHealBox.h"
#include "Interface/SPHealthInterface.h"

ASPHealBox::ASPHealBox()
{
    HealAmount = 80.0f;
}

bool ASPHealBox::GiveItem(AActor* OtherActor)
{
    Super::GiveItem(OtherActor);

    ISPHealthInterface* HealthInteface = Cast<ISPHealthInterface>(OtherActor);

    if (HealthInteface)
    {
        float BeforeHP = HealthInteface->GetHP();
        float AfterHP = HealthInteface->HealHP(HealAmount);
        return BeforeHP != AfterHP;
    }

    return false;
}
