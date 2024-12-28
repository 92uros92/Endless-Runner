// Fill out your copyright notice in the Description page of Project Settings.


#include "FloorSpawn.h"
#include "../EndlessRunnerGameMode.h"
#include "ER_Character.h"
#include "BaseObstacle.h"
#include "CoinPickup.h"
#include "Kismet/GameplayStatics.h"
#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/ArrowComponent.h"
#include "Components/BoxComponent.h"
#include "Kismet/KismetMathLibrary.h"



AFloorSpawn::AFloorSpawn()
{
	SceneComp = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComp"));
	RootComponent = SceneComp;

	AsphaltComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("AsphaltComp"));
	AsphaltComp->SetupAttachment(SceneComp);

	LeftRoadMarkingComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LeftRoadMarkingComp"));
	LeftRoadMarkingComp->SetupAttachment(SceneComp);

	RightRoadMarkingComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RightRoadMarkingComp"));
	RightRoadMarkingComp->SetupAttachment(SceneComp);

	LeftCurbComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LeftCurbComp"));
	LeftCurbComp->SetupAttachment(SceneComp);

	RightCurbComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RightCurbComp"));
	RightCurbComp->SetupAttachment(SceneComp);

	AttachPoint = CreateDefaultSubobject<UArrowComponent>(TEXT("AttachPoint"));
	AttachPoint->SetupAttachment(SceneComp);

	CenterLane = CreateDefaultSubobject<UArrowComponent>(TEXT("CenterLane"));
	CenterLane->SetupAttachment(SceneComp);

	RightLane = CreateDefaultSubobject<UArrowComponent>(TEXT("RightLane"));
	RightLane->SetupAttachment(SceneComp);

	LeftLane = CreateDefaultSubobject<UArrowComponent>(TEXT("LeftLane"));
	LeftLane->SetupAttachment(SceneComp);

	FloorSpawnBox = CreateDefaultSubobject<UBoxComponent>(TEXT("FloorSpawnBox"));
	FloorSpawnBox->SetupAttachment(SceneComp);
	FloorSpawnBox->SetCollisionProfileName(TEXT("OverlapOnlyPawn"));
}

void AFloorSpawn::BeginPlay()
{
	Super::BeginPlay();
	
	RunGameMode = Cast<AEndlessRunnerGameMode>(UGameplayStatics::GetGameMode(GetWorld()));

	check(RunGameMode);

	FloorSpawnBox->OnComponentBeginOverlap.AddDynamic(this, &AFloorSpawn::OnFloorSpawnBoxOverlap);
}

void AFloorSpawn::OnFloorSpawnBoxOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AER_Character* RunCharacter = Cast<AER_Character>(OtherActor);

	if (RunCharacter)
	{
		RunGameMode->AddFloorSurface(true);

		GetWorldTimerManager().SetTimer(DestroyHandle, this, &AFloorSpawn::DestroyFloorSurface, 2.0f, false);
	}
}

void AFloorSpawn::SpawnItems()
{
	if (IsValid(ObstacleClass) && IsValid(CoinPickupClass))
	{
		SpawnLaneItem(CenterLane);
		SpawnLaneItem(LeftLane);
		SpawnLaneItem(RightLane);
	}
}

void AFloorSpawn::SpawnLaneItem(UArrowComponent* Lane)
{
	const float RandValue = FMath::RandRange(0.0f, 1.0f);
	FActorSpawnParameters SpawnParameters;
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	const FTransform& Location = Lane->GetComponentTransform();

	if (UKismetMathLibrary::InRange_FloatFloat(RandValue, SpawnPercent1, SpawnPercent2, true, true))
	{
		ABaseObstacle* Obstacle = GetWorld()->SpawnActor<ABaseObstacle>(ObstacleClass, Location, SpawnParameters);
	}
	else if (UKismetMathLibrary::InRange_FloatFloat(RandValue, SpawnPercent3, 1.0f, true, true))
	{
		ACoinPickup* Coin = GetWorld()->SpawnActor<ACoinPickup>(CoinPickupClass, Location, SpawnParameters);
	}
}

void AFloorSpawn::DestroyFloorSurface()
{
	if (DestroyHandle.IsValid())
	{
		GetWorldTimerManager().ClearTimer(DestroyHandle);
	}

	this->Destroy();
}

const FTransform& AFloorSpawn::GetAttachTransform() const
{
	return AttachPoint->GetComponentTransform();
}
