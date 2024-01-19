// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/SPSoldier.h"
#include "SPPlayerSoldier.generated.h"

/**
 * 
 */

DECLARE_MULTICAST_DELEGATE_OneParam(FOnSetHPDelegate, float);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnSetAmmoDelegate, int);

UCLASS()
class SIMPLEFTPS_API ASPPlayerSoldier : public ASPSoldier
{
	GENERATED_BODY()

public:
	ASPPlayerSoldier();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponenet) override;

public:
	virtual void SetHP(float Value) override;
	virtual void EquipGun(class USPGunData* GunData) override;
	virtual void SetCurrentAmmo(int Value) override;

//Input function section
protected:
	void MoveForward(float Value);
	void MoveRight(float Value);
	void StartRunning();
	void StopRunning();
	void ShotInput();
	void PressReload();
	void ReleaseReload();

//View mode Section
protected:
	void ChangeViewMode();
	void SetViewModeFPS();
	void SetViewModeTPS();

protected:
	bool ShotFromShoulder();
	virtual void SetDead() override;

//Components section
protected:
	UPROPERTY(VisibleAnywhere, Category = Componenet)
	TObjectPtr<class USpringArmComponent> SpringArmComp;
	UPROPERTY(VisibleAnywhere, Category = Componenet)
	TObjectPtr<class UCameraComponent> CameraComp;
	

public:
	FOnSetHPDelegate OnSetHPDelegate;
	FOnSetAmmoDelegate OnSetMaxAmmoDelegate;
	FOnSetAmmoDelegate OnSetCurrentAmmoDelegate;

//Movement section
protected:
	UPROPERTY(VisibleAnywhere, Category = Stat)
	FVector2D MoveDirection;

protected:
	UPROPERTY(VisibleAnywhere, Category = ViewMode)
	uint32 bIsFPSMode : 1;
	
};
