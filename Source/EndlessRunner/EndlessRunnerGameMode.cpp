// Copyright Epic Games, Inc. All Rights Reserved.

#include "EndlessRunnerGameMode.h"
#include "EndlessRunnerCharacter.h"
#include "FloorSpawn.h"
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
	for (int i = 0; i < NumInitialFloorSurfaces; i++)
	{
		AddFloorSurface();
	}
}

void AEndlessRunnerGameMode::AddFloorSurface()
{
	UWorld* World = GetWorld();

	if (World)
	{
		AFloorSpawn* FloorSpawn = World->SpawnActor<AFloorSpawn>(FloorSpawnClass, NextFloorSpawnPoint);

		if (FloorSpawn)
		{
			NextFloorSpawnPoint = FloorSpawn->GetAttachTransform();
		}
	}
}