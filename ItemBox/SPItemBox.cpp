// Fill out your copyright notice in the Description page of Project Settings.


#include "SPItemBox.h"
#include "Components/BoxComponent.h"

// Sets default values
ASPItemBox::ASPItemBox()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxCollisionComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollisionComp"));
	RootComponent = BoxCollisionComp;

	BoxCollisionComp->SetCollisionProfileName(TEXT("supplies"));

	//StaticMeshs init

	FloorMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FloorMeshComp"));
	FloorMeshComp->SetupAttachment(RootComponent);

	BoxMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BoxMeshComp"));
	BoxMeshComp->SetupAttachment(RootComponent);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> CubeMeshRef(TEXT("/Script/Engine.StaticMesh'/Engine/BasicShapes/Cube.Cube'"));
	if (CubeMeshRef.Object)
	{
		FloorMeshComp->SetStaticMesh(CubeMeshRef.Object);
		BoxMeshComp->SetStaticMesh(CubeMeshRef.Object);
	}

	static ConstructorHelpers::FObjectFinder<UMaterialInterface> CubeMaterialRef(TEXT("/Script/Engine.Material'/Engine/BasicShapes/BasicShapeMaterial.BasicShapeMaterial'"));
	if (CubeMaterialRef.Object)
	{
		FloorMeshComp->SetMaterial(0, CubeMaterialRef.Object);
		BoxMeshComp->SetMaterial(0, CubeMaterialRef.Object);
	}

	FloorMeshComp->SetRelativeScale3D(FVector(0.65f, 0.65f, 0.1f));
	FloorMeshComp->SetRelativeLocation(FVector(0.0f, 0.0f, -27.0f));
	FloorMeshComp->SetCollisionProfileName(TEXT("NoCollision"));

	BoxMeshComp->SetRelativeScale3D(FVector(0.4f, 0.4f, 0.4f));
	BoxMeshComp->SetRelativeLocation(FVector(0.0f, 0.0f, 5.0f));
	BoxMeshComp->SetCollisionProfileName(TEXT("NoCollision"));
	
	ReloadCoolTime = 5.0f;
	SetbIsReload(true);
}

// Called when the game starts or when spawned
void ASPItemBox::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASPItemBox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	BoxMeshComp->AddRelativeRotation(FRotator(0.0f, 90.0f * DeltaTime,0.0f));
}

void ASPItemBox::NotifyActorBeginOverlap(AActor* OtherActor)
{
	if (!bIsReloaded) 
	{
		return;
	}

	bool GiveResult = GiveItem(OtherActor);

	if (GiveResult) 
	{
		SetbIsReload(false);

		GetWorld()->GetTimerManager().SetTimer(ReloadTimerHandle, FTimerDelegate::CreateLambda([&]()
			{
				SetbIsReload(true);
			}), ReloadCoolTime, false); 
	}
}

bool ASPItemBox::GiveItem(AActor* OtherActor)
{
	return true;
}

void ASPItemBox::SetbIsReload(bool NewbIsReload)
{
	bIsReloaded = NewbIsReload;
	BoxMeshComp->SetVisibility(NewbIsReload);
}

