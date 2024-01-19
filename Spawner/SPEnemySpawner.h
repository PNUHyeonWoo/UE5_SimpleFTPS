// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SPEnemySpawner.generated.h"

UCLASS()
class SIMPLEFTPS_API ASPEnemySpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASPEnemySpawner();

protected:
	virtual void PostInitProperties() override;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


protected:
	UPROPERTY(VisibleAnywhere, Category = Item)
	FTimerHandle SpawnTimerHandle;

	const float SpawnCoolTime = 10.0f;
};
