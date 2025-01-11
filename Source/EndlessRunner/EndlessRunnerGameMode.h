// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "EndlessRunnerGameMode.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCoinsCountChanged, int32, CoinsCount);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnLivesCountChanged, int32, LivesCount);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHighScoreChanged, int32, NewHighScore);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnLevelReset);


UCLASS(minimalapi)
class AEndlessRunnerGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, Category = "Components")
	TSubclassOf<class UUserWidget> GPWidgetClass;

	UPROPERTY(EditAnywhere, Category = "Components")
	TSubclassOf<class AFloorSpawn> FloorSpawnClass;

	UPROPERTY(EditAnywhere, Category = "Components")
	TSubclassOf<class UUserWidget> GameOverScreenClass;

	UPROPERTY(VisibleInstanceOnly, Category = "Runtime")
	class UGamePlayWidget* GamePlayWidget;

	UPROPERTY(VisibleAnywhere, Category = "Score")
	int32 TotalCoins;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Score")
	int32 HighScore;

	UPROPERTY(VisibleAnywhere, Category = "Score")
	class UER_SaveGame* SaveGameInstance;

	UPROPERTY(VisibleAnywhere)
	int32 NumOfLives;

	UPROPERTY(EditAnywhere)
	int32 MaxLives;

	UPROPERTY(EditAnywhere, Category = "Components")
	int32 NumInitialFloorSurfaces;

	UPROPERTY(VisibleInstanceOnly, Category = "Runtime")
	FTransform NextFloorSpawnPoint;

	UPROPERTY(VisibleInstanceOnly, Category = "Runtime")
	TArray<float> LaneSwitchValues;

	UPROPERTY(VisibleInstanceOnly, Category = "Runtime")
	TArray<AFloorSpawn*> FloorSurfaces;

	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "Events")
	FOnCoinsCountChanged OnCoinsCountChanged;

	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "Events")
	FOnLivesCountChanged OnLivesCountChanged;

	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "Events")
	FOnHighScoreChanged OnHighScoreChanged;

	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "Events")
	FOnLevelReset OnLevelReset;


	AEndlessRunnerGameMode();

	UFUNCTION(BlueprintCallable)
	void CreateInitialFloorSurfaces();

	UFUNCTION(BlueprintCallable)
	class AFloorSpawn* AddFloorSurface(const bool bSpawnItems);

	UFUNCTION(BlueprintCallable)
	void GameOver();

	UFUNCTION(BlueprintCallable)
	void AddCoin();

	UFUNCTION(BlueprintCallable)
	void PlayerDied();

	UFUNCTION(BlueprintCallable)
	void RemoveSurface(AFloorSpawn* Surface);

	UFUNCTION(BlueprintCallable)
	void SaveHighScore();

	UFUNCTION(BlueprintCallable)
	void LoadHighScore();

protected:

	virtual void BeginPlay() override;
};



