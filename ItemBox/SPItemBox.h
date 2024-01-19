// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SPItemBox.generated.h"

UCLASS()
class SIMPLEFTPS_API ASPItemBox : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASPItemBox();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
	virtual bool GiveItem(AActor* OtherActor);

protected:
	void SetbIsReload(bool NewbIsReload);

protected:
	UPROPERTY(VisibleAnywhere, Category = Componenet)
	TObjectPtr<class UBoxComponent> BoxCollisionComp;
	UPROPERTY(VisibleAnywhere, Category = Componenet)
	TObjectPtr<class UStaticMeshComponent> FloorMeshComp;
	UPROPERTY(VisibleAnywhere, Category = Componenet)
	TObjectPtr<class UStaticMeshComponent> BoxMeshComp;

protected:
	UPROPERTY(EditAnywhere, Category = Item)
	float ReloadCoolTime;
	UPROPERTY(VisibleAnywhere, Category = Item)
	FTimerHandle ReloadTimerHandle;

	UPROPERTY(VisibleAnywhere, Category = Item)
	uint8 bIsReloaded : 1;
	

};
