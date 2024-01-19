// Fill out your copyright notice in the Description page of Project Settings.


#include "Spawner/SPEnemySpawner.h"
#include "Character/SPEnemySoldier.h"
#include "NavigationSystem.h"

// Sets default values
ASPEnemySpawner::ASPEnemySpawner()
{
	PrimaryActorTick.bCanEverTick = false;
}

void ASPEnemySpawner::PostInitProperties()
{
	Super::PostInitProperties();
	ASPEnemySoldier::SetNumOfEnemySoldier(0);
}

// Called when the game starts or when spawned
void ASPEnemySpawner::BeginPlay()
{
	Super::BeginPlay();

	GetWorld()->GetTimerManager().SetTimer(SpawnTimerHandle, FTimerDelegate::CreateLambda([&]()
		{
			if (ASPEnemySoldier::GetNumOfEnemySoldier() < 5)
			{
				FNavLocation SpawnLocation;
				UNavigationSystemV1::GetNavigationSystem(GetWorld())->GetRandomReachablePointInRadius(FVector(0, 0, 0), 10000.0f,SpawnLocation);
				GetWorld()->SpawnActor<ASPEnemySoldier>(SpawnLocation.Location + FVector(0,0,90.0f), FRotator(0,0,0));
			}
		}), SpawnCoolTime,true);
	
}

