// Fill out your copyright notice in the Description page of Project Settings.


#include "Notify/SPInsertMagazine.h"
#include "Interface/SPGunInterface.h"

void USPInsertMagazine::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	ISPGunInterface* GunInterface = Cast<ISPGunInterface>(MeshComp->GetOwner());
	if (GunInterface)
	{
		GunInterface->InsertMagazine();
	}
}
