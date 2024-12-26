// Fill out your copyright notice in the Description page of Project Settings.


#include "FloorSpawn.h"
#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/ArrowComponent.h"
#include "Components/BoxComponent.h"



AFloorSpawn::AFloorSpawn()
{
	PrimaryActorTick.bCanEverTick = true;

	SceneComp = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComp"));
	RootComponent = SceneComp;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	MeshComp->SetupAttachment(SceneComp);

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
	
}

void AFloorSpawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

