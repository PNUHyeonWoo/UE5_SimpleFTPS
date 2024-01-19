// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimInstance/SPSoldierAnimInstance.h"
#include "Character/SPSoldier.h"


USPSoldierAnimInstance::USPSoldierAnimInstance()
{
	UpperBodyWeight = 1.0f;
	UpperBodySmoothWeight = 1.0f;
}

void USPSoldierAnimInstance::NativeUpdateAnimation(float DeltaTime)
{
	Super::NativeUpdateAnimation(DeltaTime);

	APawn* Pawn = TryGetPawnOwner();

	if (Pawn)
	{
		FVector2D Velocity2D(Pawn->GetVelocity());
		FVector2D ControlRotation2D(FRotationMatrix(Pawn->GetActorRotation()).GetUnitAxis(EAxis::X));

		Speed = Velocity2D.Length();

		Velocity2D.Normalize();
		ControlRotation2D.Normalize();

		if (Speed > 0.01f)
		{
			float Angle = acosf(Velocity2D.Dot(ControlRotation2D)) * 180.0f/PI;
			float Det = ControlRotation2D.X * Velocity2D.Y - ControlRotation2D.Y * Velocity2D.X;
			if (Det > 0)
			{
				Angle = 360 - Angle;
			}
			RelativeMovingAngle = Angle;	
		}

		if (Speed < 300.0f) 
		{
			UpperBodyWeight = 1.0f;
		}
		else 
		{
			UpperBodyWeight = 1.0f - FMath::Clamp((Speed - 300.0f) / 400.0f, 0.0f, 1.0f);	
		}


		ControlPitch = Pawn->GetControlRotation().Pitch;
		if (ControlPitch > 180)
		{
			ControlPitch -= 360;
		}

		ASPSoldier* Soldier = Cast<ASPSoldier>(Pawn);
		if (Soldier) 
		{
			bIsTryingToReload = Soldier->GetIsTryingToReload();
		}

	}

	if (UpperBodySmoothWeight < UpperBodyWeight)
	{
		UpperBodySmoothWeight = FMath::Clamp(UpperBodySmoothWeight + SmoothWeightAcceleration * DeltaTime, 0.0f, UpperBodyWeight);
	}
	else if (UpperBodySmoothWeight > UpperBodyWeight)
	{
		UpperBodySmoothWeight = FMath::Clamp(UpperBodySmoothWeight - SmoothWeightAcceleration * DeltaTime, UpperBodyWeight, 1.0f);
	}
	




}

void USPSoldierAnimInstance::InsertMagazine()
{
	APawn* Pawn = TryGetPawnOwner();

	if (Pawn) 
	{
		ISPGunInterface* GunInterface = Cast<ISPGunInterface>(Pawn);
		if (GunInterface) 
		{
			GunInterface->InsertMagazine();
		}
	
	}
}
