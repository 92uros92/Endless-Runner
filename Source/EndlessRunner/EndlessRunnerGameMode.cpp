// Copyright Epic Games, Inc. All Rights Reserved.

#include "EndlessRunnerGameMode.h"
#include "EndlessRunnerCharacter.h"
#include "FloorSpawn.h"
#include "GamePlayWidget.h"
#include "ER_SaveGame.h"
#include "Components/ArrowComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/UserWidget.h"



AEndlessRunnerGameMode::AEndlessRunnerGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	TotalCoins = 0;
	MaxLives = 3;
	NumOfLives = 0;
	NumInitialFloorSurfaces = 10;
}

void AEndlessRunnerGameMode::BeginPlay()
{
	Super::BeginPlay();

	UGameplayStatics::GetPlayerController(GetWorld(), 0)->bShowMouseCursor = true;

	LoadHighScore();

	GamePlayWidget = Cast<UGamePlayWidget>(CreateWidget(GetWorld(), GPWidgetClass));
	check(GamePlayWidget);

	GamePlayWidget->InitializeWidget(this);
	GamePlayWidget->AddToViewport();

	NumOfLives = MaxLives;

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
			FloorSurfaces.Add(FloorSpawn);

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

void AEndlessRunnerGameMode::AddCoin()
{
	TotalCoins += 1;
	//UE_LOG(LogTemp, Warning, TEXT("Total Coins: %d"), TotalCoins);

	OnCoinsCountChanged.Broadcast(TotalCoins);

	if (TotalCoins > HighScore)
	{
		HighScore = TotalCoins;
		
		SaveHighScore();
	}
}

void AEndlessRunnerGameMode::SaveHighScore()
{
	SaveGameInstance = Cast<UER_SaveGame>(UGameplayStatics::CreateSaveGameObject(UER_SaveGame::StaticClass()));

	if (SaveGameInstance)
	{
		SaveGameInstance->HighScore = HighScore;

		OnHighScoreChanged.Broadcast(HighScore); 

		UGameplayStatics::SaveGameToSlot(SaveGameInstance, TEXT("HighScoreSlot"), 0);
	}
}

void AEndlessRunnerGameMode::LoadHighScore()
{
	if (UGameplayStatics::DoesSaveGameExist(TEXT("HighScoreSlot"), 0))
	{
		SaveGameInstance = Cast<UER_SaveGame>(UGameplayStatics::LoadGameFromSlot(TEXT("HighScoreSlot"), 0));

		if (SaveGameInstance)
		{
			HighScore = SaveGameInstance->HighScore;
			
			UE_LOG(LogTemp, Warning, TEXT("High Score: %i"), HighScore);
		}
	}
	else
	{
		HighScore = 0;
	}
}

void AEndlessRunnerGameMode::PlayerDied()
{
	NumOfLives -= 1;
	OnLivesCountChanged.Broadcast(NumOfLives);

	if (NumOfLives > 0)
	{
		// Iterate all FloorSurfaces and call DestroyFloorSurface
		for (auto Surface : FloorSurfaces)
		{
			Surface->DestroyFloorSurface();
		}

		// Empty array
		FloorSurfaces.Empty();

		// Set NextSpawnPoint to initial value 
		NextFloorSpawnPoint = FTransform();

		// Create initial floor surfaces
		CreateInitialFloorSurfaces();

		// Broadcast level reset event
		OnLevelReset.Broadcast();
	}
	else
	{
		GameOver();
	}
}

void AEndlessRunnerGameMode::GameOver()
{
	if (IsValid(GameOverScreenClass))
	{
		UUserWidget* Widget = CreateWidget(GetWorld(), GameOverScreenClass);

		if (Widget)
		{
			Widget->AddToViewport();
		}
	}
}

void AEndlessRunnerGameMode::RemoveSurface(AFloorSpawn* Surface)
{
	/*TArray<AActor*> Floors;

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AFloorSpawn::StaticClass(), Floors);

	for (auto Floor : Floors)
	{

	}*/

	if (FloorSurfaces.Contains(Surface))
	{
		FloorSurfaces.Remove(Surface);
	}
}
