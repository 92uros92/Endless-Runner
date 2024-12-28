// Copyright Epic Games, Inc. All Rights Reserved.

#include "EndlessRunnerGameMode.h"
#include "EndlessRunnerCharacter.h"
#include "FloorSpawn.h"
#include "Components/ArrowComponent.h"
#include "UObject/ConstructorHelpers.h"



AEndlessRunnerGameMode::AEndlessRunnerGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}

void AEndlessRunnerGameMode::BeginPlay()
{
	Super::BeginPlay();

	CreateInitialFloorSurfaces();
}

void AEndlessRunnerGameMode::CreateInitialFloorSurfaces()
{
	AFloorSpawn* FloorSpawn = AddFloorSurface(false);

	if (FloorSpawn)
	{
		LaneSwitchValues.Add(FloorSpawn->LeftLane->GetComponentLocation().Y);
		LaneSwitchValues.Add(FloorSpawn->CenterLane->GetComponentLocation().Y);
		LaneSwitchValues.Add(FloorSpawn->RightLane->GetComponentLocation().Y);
	}

	//for (float Value : LaneSwitchValues)
	//{
	//	UE_LOG(LogTemp, Warning, TEXT("Lane Value: %f"), Value);
	//}

	AddFloorSurface(false);
	AddFloorSurface(false);

	for (int i = 0; i < NumInitialFloorSurfaces; i++)
	{
		AddFloorSurface(true);
	}
}

AFloorSpawn* AEndlessRunnerGameMode::AddFloorSurface(const bool bSpawnItems)
{
	UWorld* World = GetWorld();

	if (World)
	{
		AFloorSpawn* FloorSpawn = World->SpawnActor<AFloorSpawn>(FloorSpawnClass, NextFloorSpawnPoint);

		if (FloorSpawn)
		{
			if (bSpawnItems)
			{
				FloorSpawn->SpawnItems();
			}

			NextFloorSpawnPoint = FloorSpawn->GetAttachTransform();
		}

		return FloorSpawn;
	}

	return nullptr;
}