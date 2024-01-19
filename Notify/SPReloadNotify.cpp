// Fill out your copyright notice in the Description page of Project Settings.


#include "Notify/SPReloadNotify.h"
#include "Interface/SPGunInterface.h"

void USPReloadNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	if (MeshComp)
	{
		ISPGunInterface* GunInterface = Cast<ISPGunInterface>(MeshComp->GetOwner());
		if (GunInterface) 
		{
			GunInterface->Reload();
		}
	}
}
