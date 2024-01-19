// Fill out your copyright notice in the Description page of Project Settings.


#include "SPUserWidget.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include <GameFramework/InputSettings.h>

USPUserWidget::USPUserWidget(const FObjectInitializer& ObjectInitializer):Super(ObjectInitializer)
{
	MaxHP = 100;
}

void USPUserWidget::NativeConstruct()
{
	Super::NativeConstruct();

	HPProgressBar = Cast<UProgressBar>(GetWidgetFromName("HPBar"));
	MaxAmmo = Cast<UTextBlock>(GetWidgetFromName("MaxAmmo"));
	CurrentAmmo = Cast<UTextBlock>(GetWidgetFromName("CurrentAmmo"));
}



void USPUserWidget::SetMaxHP(float Value)
{
	MaxHP = Value;
}

void USPUserWidget::SetHP(float Value)
{
	HPProgressBar->SetPercent(Value / MaxHP);
}

void USPUserWidget::SetMaxAmmo(int Value)
{
	MaxAmmo->SetText(FText::FromString(FString::FromInt(Value)));
}

void USPUserWidget::SetCurrentAmmo(int Value)
{
	CurrentAmmo->SetText(FText::FromString(FString::FromInt(Value)));
}
