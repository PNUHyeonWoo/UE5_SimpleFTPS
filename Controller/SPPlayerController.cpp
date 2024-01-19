// Fill out your copyright notice in the Description page of Project Settings.


#include "Controller/SPPlayerController.h"
#include "UI/SPUserWidget.h"
#include "Character/SPPlayerSoldier.h"
#include "Gun/SPGunData.h"
#include "Engine/LevelStreamingDynamic.h"

ASPPlayerController::ASPPlayerController()
{
	static ConstructorHelpers::FClassFinder<USPUserWidget> SPUserWidgetClassRef(TEXT("/Game/UI/SPUserWidget.SPUserWidget_C"));
	if (SPUserWidgetClassRef.Class)
	{
		SPUserWidgetBPClass = SPUserWidgetClassRef.Class;
	}
}

void ASPPlayerController::BeginPlay()
{
	Super::BeginPlay();

	SPUserWidget = CreateWidget<USPUserWidget>(this, SPUserWidgetBPClass);
	if (SPUserWidget)
	{
		SPUserWidget->AddToViewport();
	}

	ASPPlayerSoldier* PlayerSolider = Cast<ASPPlayerSoldier>(GetPawn());

	if (PlayerSolider)
	{
		PlayerSolider->OnSetHPDelegate.AddUObject(SPUserWidget, &USPUserWidget::SetHP);
		PlayerSolider->OnSetMaxAmmoDelegate.AddUObject(SPUserWidget, &USPUserWidget::SetMaxAmmo);
		PlayerSolider->OnSetCurrentAmmoDelegate.AddUObject(SPUserWidget, &USPUserWidget::SetCurrentAmmo);
	}

	SPUserWidget->SetMaxHP(PlayerSolider->GetMaxHP());
	SPUserWidget->SetHP(PlayerSolider->GetHP());
	SPUserWidget->SetMaxAmmo(PlayerSolider->GetGun()->Capacity);
	SPUserWidget->SetCurrentAmmo(PlayerSolider->GetCurrentAmmo());

}
