// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/SPSoldier.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Gun/SPGunData.h"
#include "Interface/SPHealthInterface.h"
#include "Engine/AssetManager.h"
#include "Gun/SPGunData.h"
#include "Animation/AnimNode_StateMachine.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
#include "Animation/AnimMontage.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ASPSoldier::ASPSoldier()
{
	PrimaryActorTick.bCanEverTick = true;

	MaxHP = 100.0f;
	CurrentHP = MaxHP;
	WalkingSpeed = 300.0f;
	RunningSpeed = 700.0f;
	JumpPower = 500.0f;
	CurrentAmmo = 0;
	ShotingCoolTime = 0.0f;

	BaseEyeHeight = EyeHeight;

	//Capsule init
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("Pawn"));

	// Movement init
	GetCharacterMovement()->bOrientRotationToMovement = false;
	GetCharacterMovement()->JumpZVelocity = JumpPower;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = WalkingSpeed;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;

	SetIsRunning(false); //set Walking Mode

	//Mesh Init
	GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -88.0f), FRotator(0.0f, -90.0f, 0.0f));
	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
	GetMesh()->SetCollisionProfileName(TEXT("NoCollision"));

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> CharacterMeshRef(TEXT("/Script/Engine.SkeletalMesh'/Game/AnimStarterPack/UE4_Mannequin/Mesh/SK_Mannequin.SK_Mannequin'"));
	if (CharacterMeshRef.Object)
	{
		GetMesh()->SetSkeletalMesh(CharacterMeshRef.Object);
	}

	static ConstructorHelpers::FClassFinder<UAnimInstance> AnimInstanceClassRef(TEXT("/Game/AnimationBlueprint/SPSoldierAnimationBlueprint.SPSoldierAnimationBlueprint_C"));
	if (AnimInstanceClassRef.Class)
	{
		GetMesh()->SetAnimInstanceClass(AnimInstanceClassRef.Class);
	}

	//Componenets init
	GunMeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("GunMeshComp"));
	GunMeshComp->SetupAttachment(GetMesh(), TEXT("gunSocket"));
	MagazineMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MagazineMeshComp"));
	MagazineMeshComp->SetupAttachment(GetMesh(), TEXT("magazineSocket"));

	//Gun init
	static ConstructorHelpers::FObjectFinder<USPGunData> GunDataRef(TEXT("/Script/SimpleFTPS.SPGunData'/Game/Gun/AR1.AR1'"));

	if (GunDataRef.Object) 
	{
		EquipGun(GunDataRef.Object);
	}

	MuzzleFlashComp = CreateDefaultSubobject<UNiagaraComponent>(TEXT("MuzzleFlashComp"));
	MuzzleFlashComp->SetupAttachment(GunMeshComp, TEXT("MuzzleSocket"));
	MuzzleFlashComp->SetRelativeRotation(FRotator(90.f, 0, 0));

	static ConstructorHelpers::FObjectFinder<UNiagaraSystem> MuzzleFlashRef(TEXT("/Script/Niagara.NiagaraSystem'/Game/Effect/MuzzleFlash.MuzzleFlash'"));

	if (MuzzleFlashRef.Object)
	{
		MuzzleFlashComp->SetAsset(MuzzleFlashRef.Object);
	}

	static ConstructorHelpers::FObjectFinder<USoundWave> FireSoundRef(TEXT("/Script/Engine.SoundWave'/Game/Sound/Shot.Shot'"));

	if (FireSoundRef.Object)
	{
		FireSound = FireSoundRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UAnimMontage> DeadMontageRef(TEXT("/Script/Engine.AnimMontage'/Game/Montage/DeadMontage.DeadMontage'"));
	
	if (DeadMontageRef.Object)
	{
		DeadMontage = DeadMontageRef.Object;
	}

}

// Called when the game starts or when spawned
void ASPSoldier::BeginPlay()
{
	Super::BeginPlay();
	InsertMagazine();
	MuzzleFlashComp->SetPaused(true);
}

// Called every frame
void ASPSoldier::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (ShotingCoolTime > 0.0f)
	{
		ShotingCoolTime -= DeltaTime;
	}

	if (!bIsRunning && WalkingSpeed < GetCharacterMovement()->MaxWalkSpeed)
	{
		GetCharacterMovement()->MaxWalkSpeed = FMath::Clamp(GetCharacterMovement()->MaxWalkSpeed + DeltaTime * RunningToWalkingAcceleration,WalkingSpeed,10000.0f);
	}

}

// Called to bind functionality to input
void ASPSoldier::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

float ASPSoldier::GetHP()
{
	return CurrentHP;
}

float ASPSoldier::HealHP(float HealAmount)
{
	SetHP(FMath::Clamp(CurrentHP + HealAmount, 0, MaxHP));
	return CurrentHP;
}

float ASPSoldier::DamageHP(float DamageAmount)
{
	SetHP(FMath::Clamp(CurrentHP - DamageAmount, 0, MaxHP));
	if (CurrentHP <= 0) 
	{
		SetDead();
	}
	return CurrentHP;
}

USPGunData* ASPSoldier::GetGun()
{
	return EquipedGun;
}

void ASPSoldier::EquipGun(USPGunData* GunData)
{
	EquipedGun = GunData;
	Reload();
	if (GunData->GunMesh.IsPending()) 
	{
		GunData->GunMesh.LoadSynchronous();
	}
	GunMeshComp->SetSkeletalMesh(GunData->GunMesh.Get());

	if (GunData->MagazineMesh.IsPending())
	{
		GunData->MagazineMesh.LoadSynchronous();
	}
	MagazineMeshComp->SetStaticMesh(GunData->MagazineMesh.Get());

}

void ASPSoldier::Reload()
{
	SetCurrentAmmo(EquipedGun->Capacity);
}

void ASPSoldier::RemoveMagazine()
{
	MagazineMeshComp->SetVisibility(true);
	GunMeshComp->HideBoneByName(TEXT("b_gun_mag"),EPhysBodyOp::PBO_None);
}

void ASPSoldier::InsertMagazine()
{
	MagazineMeshComp->SetVisibility(false);
	GunMeshComp->UnHideBoneByName(TEXT("b_gun_mag"));
}

float ASPSoldier::GetMaxHP()
{
	return MaxHP;
}

int ASPSoldier::GetCurrentAmmo()
{
	return CurrentAmmo;
}

void ASPSoldier::SetHP(float Value)
{
	CurrentHP = FMath::Clamp(Value, 0, MaxHP);
}

bool ASPSoldier::GetIsTryingToReload()
{
	return bIsTryingToReload;
}

void ASPSoldier::SetIsTryingToReload(bool Value)
{
	bIsTryingToReload = Value;
}

void ASPSoldier::SetCurrentAmmo(int Value)
{
	CurrentAmmo = Value;
}

bool ASPSoldier::Shot(FVector Start, FVector End)
{
	FName CurrentStateName = GetMesh()->GetAnimInstance()->GetStateMachineInstanceFromName(TEXT("UpperBody"))->GetCurrentStateName();

	if (CurrentAmmo <= 0 || ShotingCoolTime > 0.0f || CurrentStateName != TEXT("Aiming"))
	{
		return false;
	}
	SetCurrentAmmo(CurrentAmmo - 1);
	MuzzleFlashComp->ResetSystem();
	UGameplayStatics::PlaySoundAtLocation(this, FireSound, GetActorLocation());

	ShotingCoolTime = EquipedGun->ShootingCoolTime;

	FHitResult HResult;

	FCollisionQueryParams Params(SCENE_QUERY_STAT(Shot), false, this);

	bool IsHit = GetWorld()->LineTraceSingleByChannel(HResult, Start, End, ECC_GameTraceChannel1, Params);

	if(IsHit)
	{
		ISPHealthInterface* Target = Cast<ISPHealthInterface>(HResult.GetActor());
		if (Target) 
		{
			Target->DamageHP(EquipedGun->GunDamage);
		}
	}	

	//DrawDebugLine(GetWorld(), Start, End, FColor::Green, false, 1.0f,0U,3.0f);

	return true;
}

bool ASPSoldier::ShotFromEye()
{
	FVector EyeLocation = RootComponent->GetComponentLocation();
	EyeLocation.Z += EyeHeight;
	FVector Target = EyeLocation + (FRotationMatrix(GetController()->GetControlRotation()).GetUnitAxis(EAxis::X) * ShotRange);

	return Shot(EyeLocation,Target);
}

void ASPSoldier::SetIsRunning(bool Value)
{
	bIsRunning = Value;
	if (Value)
	{
		GetCharacterMovement()->MaxWalkSpeed = RunningSpeed;
	}
}

void ASPSoldier::SetDead()
{
	GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_None);
	SetActorEnableCollision(false);
	GetMesh()->GetAnimInstance()->Montage_Play(DeadMontage);
}

