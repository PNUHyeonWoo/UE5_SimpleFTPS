// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/SPEnemySoldier.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Controller//SPEnemySoldierAIController.h"

int ASPEnemySoldier::NumOfEnemySoldier = 0;

ASPEnemySoldier::ASPEnemySoldier()
{
	SetViewModeMoving();

	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	AIControllerClass = ASPEnemySoldierAIController::StaticClass();
}

void ASPEnemySoldier::BeginPlay()
{
	Super::BeginPlay();
	NumOfEnemySoldier += 1;
}

void ASPEnemySoldier::SetViewModeMoving()
{
	GetCharacterMovement()->bOrientRotationToMovement = true;
	bUseControllerRotationYaw = false;
}

void ASPEnemySoldier::SetViewModeAttacking()
{
	GetCharacterMovement()->bOrientRotationToMovement = false;
	bUseControllerRotationYaw = true;
}

void ASPEnemySoldier::ShotFromAI()
{
	ShotFromEye();
}

int ASPEnemySoldier::GetNumOfEnemySoldier()
{
	return NumOfEnemySoldier;
}

void ASPEnemySoldier::SetNumOfEnemySoldier(int Value)
{
	NumOfEnemySoldier = Value;
}

void ASPEnemySoldier::Tick(float deltaTime)
{
	Super::Tick(deltaTime);

	SetIsTryingToReload(CurrentAmmo <= 0);
	
}

void ASPEnemySoldier::SetDead()
{
	Super::SetDead();
	ASPEnemySoldierAIController *EnemyController = Cast<ASPEnemySoldierAIController>(GetController());
	if (EnemyController)
	{
		EnemyController->StopBT();
	}

	GetCharacterMovement()->bOrientRotationToMovement = false;
	bUseControllerRotationYaw = false;

	NumOfEnemySoldier -= 1;
}
