// Fill out your copyright notice in the Description page of Project Settings.


#include "BT/BTService_SetCanSeeTarget.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTService_SetCanSeeTarget::UBTService_SetCanSeeTarget()
{
	NodeName = TEXT("SetCanSeeTarget");
	Interval = 0.5f;
	RandomDeviation = 0.0f;
}

void UBTService_SetCanSeeTarget::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSecond)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSecond);

	APawn* OwnerPawn = OwnerComp.GetAIOwner()->GetPawn();

	FHitResult HResult;

	FCollisionQueryParams Params(SCENE_QUERY_STAT(BT_SetCanSeeTarget), false, OwnerPawn);

	FVector Start = OwnerPawn->GetActorLocation() + FVector(0, 0, 80.0f);
	UBlackboardComponent* BBComp = OwnerComp.GetAIOwner()->GetBlackboardComponent();
	FVector End = Cast<APawn>(BBComp->GetValueAsObject(TEXT("Target")))->GetActorLocation();

	bool IsHit = GetWorld()->LineTraceSingleByChannel(HResult, Start, End, ECC_GameTraceChannel1, Params);

	if (IsHit)
	{
		APawn* HitPawn = Cast<APawn>((HResult.GetActor()));
		if (HitPawn)
		{
			 BBComp->SetValueAsBool(TEXT("CanSeeTarget"), HitPawn->GetController()->IsPlayerController());
			 return;
		}
	}

	BBComp->SetValueAsBool(TEXT("CanSeeTarget"), false);
	return;

}
