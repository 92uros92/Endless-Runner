// Permission to use, copy, modify, and/or distribute this software for any purpose with or without fee is hereby granted.


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
	if (IsValid(YellowObstacleClass) && IsValid(BlueObstacleClass) && IsValid(CoinPickupClass))
	{
		int32 BigObstacle = 0;
		SpawnLaneItem(CenterLane, BigObstacle);
		SpawnLaneItem(LeftLane, BigObstacle);
		SpawnLaneItem(RightLane, BigObstacle);
	}
}

void AFloorSpawn::SpawnLaneItem(UArrowComponent* Lane, int32& BigObstacle)
{
	const float RandValue = FMath::RandRange(0.0f, 1.0f);
	FActorSpawnParameters SpawnParameters;
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	const FTransform& Location = Lane->GetComponentTransform();

	// Spawn obstacle if value is between 0,1 and 0,4
	if (UKismetMathLibrary::InRange_FloatFloat(RandValue, SpawnPercent1, SpawnPercent2, true, true))
	{
		ABaseObstacle* YellowObstacle = GetWorld()->SpawnActor<ABaseObstacle>(YellowObstacleClass, Location, SpawnParameters);
		ChildActors.Add(YellowObstacle);
	}
	// Spawn obstacle if value is between 0,4 and 0,7
	else if (UKismetMathLibrary::InRange_FloatFloat(RandValue, SpawnPercent2, SpawnPercent3, true, true))
	{
		// Adding number to BigObstacle as it gets spawned on each lane.
		// If there are already two BlueObstacle then spawn YellowObstacle or no obstacle
		if (BigObstacle < 2)
		{
			ABaseObstacle* BlueObstacle = GetWorld()->SpawnActor<ABaseObstacle>(BlueObstacleClass, Location, SpawnParameters);
			ChildActors.Add(BlueObstacle);

			if (BlueObstacle)
			{
				BigObstacle += 1;
			}
			else
			{
				ABaseObstacle* YellowObstacle = GetWorld()->SpawnActor<ABaseObstacle>(YellowObstacleClass, Location, SpawnParameters);
				ChildActors.Add(YellowObstacle);
			}
		}
	}
	// Spawn coin if value is between 0,7 and 1
	else if (UKismetMathLibrary::InRange_FloatFloat(RandValue, SpawnPercent3, 1.0f, true, true))
	{
		ACoinPickup* Coin = GetWorld()->SpawnActor<ACoinPickup>(CoinPickupClass, Location, SpawnParameters);
		ChildActors.Add(Coin);
	}
}

void AFloorSpawn::DestroyFloorSurface()
{
	if (DestroyHandle.IsValid())
	{
		GetWorldTimerManager().ClearTimer(DestroyHandle);
	}

	for (auto Child : ChildActors)
	{
		if (IsValid(Child))
		{
			Child->Destroy();
		}
	}

	ChildActors.Empty();

	for (AFloorSpawn* Floor : FloorSurfaces)
	{
		if (IsValid(Floor))
		{
			Floor->Destroy();
		}
	}

	FloorSurfaces.Empty();
	
	//RunGameMode->RemoveSurface(this);

	this->Destroy();
}

const FTransform& AFloorSpawn::GetAttachTransform() const
{
	return AttachPoint->GetComponentTransform();
}
