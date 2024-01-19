// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interface/SPHealthInterface.h"
#include "Interface/SPGunInterface.h"
#include "SPSoldier.generated.h"

UCLASS()
class SIMPLEFTPS_API ASPSoldier : public ACharacter, public ISPHealthInterface, public ISPGunInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASPSoldier();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


//Interface functions
public:
	virtual float GetHP() override;
	virtual float HealHP(float HealAmount) override;
	virtual float DamageHP(float DamageAmount) override;
	virtual class USPGunData* GetGun() override;
	virtual void EquipGun(class USPGunData* GunData) override;
	virtual void Reload() override;
	virtual void RemoveMagazine() override;
	virtual void InsertMagazine() override;


public:
	float GetMaxHP();
	int GetCurrentAmmo();
	virtual void SetHP(float Value);
	bool GetIsTryingToReload();
	void SetIsTryingToReload(bool Value);
	virtual void SetCurrentAmmo(int Value);

protected:
	bool Shot(FVector Start,FVector End);
	bool ShotFromEye();
	void SetIsRunning(bool Value);
	virtual void SetDead();

//Componenet section
protected:
	UPROPERTY(VisibleAnywhere, Category = Componenet)
	TObjectPtr<class USkeletalMeshComponent> GunMeshComp;

	UPROPERTY(VisibleAnywhere, Category = Componenet)
	TObjectPtr<class UNiagaraComponent> MuzzleFlashComp;
	
	UPROPERTY(VisibleAnywhere, Category = Componenet)
	TObjectPtr<class UStaticMeshComponent> MagazineMeshComp;

//Health section
protected:
	UPROPERTY(EditAnywhere, Category = Stat)
	float MaxHP;
	UPROPERTY(EditAnywhere, Category = Stat)
	float CurrentHP;

//Movement section
protected:
	UPROPERTY(VisibleAnywhere, Category = Stat)
	uint32 bIsRunning : 1;
	UPROPERTY(EditAnywhere, Category = Stat)
	float WalkingSpeed;
	UPROPERTY(EditAnywhere, Category = Stat)
	float RunningSpeed;
	UPROPERTY(EditAnywhere, Category = Stat)
	float JumpPower;

//Gun section
protected:
	UPROPERTY(VisibleAnywhere, Category = Gun)
	TObjectPtr<class USPGunData> EquipedGun;

	UPROPERTY(VisibleAnywhere, Category = Gun)
	uint32 bIsTryingToReload : 1;

	UPROPERTY(EditAnywhere, Category = Gun)
	uint32 CurrentAmmo;
	UPROPERTY(EditAnywhere, Category = Gun)
	float ShotingCoolTime;

	UPROPERTY(VisibleAnywhere, Category = Gun)
	TObjectPtr<class USoundWave> FireSound;

	const float ShotRange = 100000.0f;
	const float EyeHeight = 80.0f;
	const float RunningToWalkingAcceleration = -1000.0f;

//Montage Section
protected:
	UPROPERTY()
	TObjectPtr<class UAnimMontage> DeadMontage;


};
