// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/SPPlayerSoldier.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Gun/SPGunData.h"
#include "Internationalization/Text.h"
#include <Internationalization/StringTableRegistry.h>
#include <GameFramework/InputSettings.h>


ASPPlayerSoldier::ASPPlayerSoldier()
{
	MaxHP = 1000.0f;
	CurrentHP = MaxHP;

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComp"));
	SpringArmComp->SetupAttachment(RootComponent);
	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));
	CameraComp->SetupAttachment(SpringArmComp, USpringArmComponent::SocketName);

}

void ASPPlayerSoldier::BeginPlay()
{
	Super::BeginPlay();
	SetViewModeTPS();
}

void ASPPlayerSoldier::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FRotator Yaw(0, Controller->GetControlRotation().Yaw, 0);

	FVector Forward = FRotationMatrix(Yaw).GetUnitAxis(EAxis::X) * MoveDirection.X;
	FVector Right = FRotationMatrix(Yaw).GetUnitAxis(EAxis::Y) * MoveDirection.Y;
	FVector Direction = Forward + Right;
	Direction.Normalize();
	AddMovementInput(Direction, 1.0f);

}

void ASPPlayerSoldier::SetupPlayerInputComponent(UInputComponent* PlayerInputComponenet)
{
	Super::SetupPlayerInputComponent(PlayerInputComponenet);
	
	InputComponent->BindAxis("WS", this, &ASPPlayerSoldier::MoveForward);
	InputComponent->BindAxis("DA", this, &ASPPlayerSoldier::MoveRight);
	InputComponent->BindAxis("MouseX", this, &ASPPlayerSoldier::AddControllerYawInput);
	InputComponent->BindAxis("MouseY", this, &ASPPlayerSoldier::AddControllerPitchInput);
	InputComponent->BindAction("MouseLeft",IE_Pressed, this, &ASPPlayerSoldier::ShotInput);
	InputComponent->BindAction("V", IE_Pressed, this, &ASPPlayerSoldier::ChangeViewMode);
	InputComponent->BindAction("Space", IE_Pressed, this, &ASPPlayerSoldier::Jump);
	InputComponent->BindAction("Space", IE_Released, this, &ASPPlayerSoldier::StopJumping);
	InputComponent->BindAction("Shift", IE_Pressed, this, &ASPPlayerSoldier::StartRunning);
	InputComponent->BindAction("Shift", IE_Released, this, &ASPPlayerSoldier::StopRunning);
	InputComponent->BindAction("R", IE_Pressed, this, &ASPPlayerSoldier::PressReload);
	InputComponent->BindAction("R", IE_Released, this, &ASPPlayerSoldier::ReleaseReload);
	
}


void ASPPlayerSoldier::SetHP(float Value)
{
	Super::SetHP(Value);
	OnSetHPDelegate.Broadcast(CurrentHP);
}

void ASPPlayerSoldier::EquipGun(USPGunData* GunData)
{
	Super::EquipGun(GunData);
	OnSetMaxAmmoDelegate.Broadcast(EquipedGun->Capacity);
}

void ASPPlayerSoldier::SetCurrentAmmo(int Value)
{
	Super::SetCurrentAmmo(Value);
	OnSetCurrentAmmoDelegate.Broadcast(CurrentAmmo);
}



void ASPPlayerSoldier::MoveForward(float Value)
{
	MoveDirection.X = Value;
}

void ASPPlayerSoldier::MoveRight(float Value)
{
	MoveDirection.Y = Value;
}

void ASPPlayerSoldier::StartRunning()
{
	SetIsRunning(true);
}

void ASPPlayerSoldier::StopRunning()
{
	SetIsRunning(false);
}

void ASPPlayerSoldier::ShotInput()
{

	if (bIsFPSMode)
	{
		ShotFromEye();
	}
	else
	{
		ShotFromShoulder();
	}
}

void ASPPlayerSoldier::PressReload()
{
	SetIsTryingToReload(true);
}

void ASPPlayerSoldier::ReleaseReload()
{
	SetIsTryingToReload(false);
}

void ASPPlayerSoldier::ChangeViewMode()
{
	if (bIsFPSMode) 
	{
		SetViewModeTPS();
	}
	else
	{
		SetViewModeFPS();
	}

}

void ASPPlayerSoldier::SetViewModeFPS()
{
	bIsFPSMode = true;

	SpringArmComp->TargetArmLength = 0.0f;
	SpringArmComp->SocketOffset = FVector(0.0f, 0.0f, EyeHeight);
	SpringArmComp->bUsePawnControlRotation = false;
	CameraComp->bUsePawnControlRotation = true;
	GetMesh()->HideBoneByName("pelvis", EPhysBodyOp::PBO_None);
}

void ASPPlayerSoldier::SetViewModeTPS()
{
	bIsFPSMode = false;

	SpringArmComp->TargetArmLength = 200.0f;
	SpringArmComp->SocketOffset = FVector(0.0f, 100.0f, 100.0f);
	SpringArmComp->bUsePawnControlRotation = true;
	CameraComp->SetRelativeRotation(FRotator(0.0f,0.0f,0.0f));
	CameraComp->bUsePawnControlRotation = false;
	GetMesh()->UnHideBoneByName("pelvis");
}

bool ASPPlayerSoldier::ShotFromShoulder()
{
	FVector StartLocation = CameraComp->GetComponentLocation();
	FVector FrontVector = FRotationMatrix(GetController()->GetControlRotation()).GetUnitAxis(EAxis::X);
	StartLocation += FrontVector * SpringArmComp->TargetArmLength;
	FVector Target = StartLocation + (FrontVector * ShotRange);

	return Shot(StartLocation,Target);
}

void ASPPlayerSoldier::SetDead()
{
	Super::SetDead();
	APlayerController *PlayerController  = Cast<APlayerController>(GetController());
	if (PlayerController)
	{
		DisableInput(PlayerController);
	}
}
