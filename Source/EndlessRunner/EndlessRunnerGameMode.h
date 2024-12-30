// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "EndlessRunnerGameMode.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCoinsCountChanged, int32, CoinsCount);

UCLASS(minimalapi)
class AEndlessRunnerGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, Category = "Components")
	TSubclassOf<class UUserWidget> GPWidgetClass;

	UPROPERTY(EditAnywhere, Category = "Components")
	TSubclassOf<class AFloorSpawn> FloorSpawnClass;

	UPROPERTY(VisibleInstanceOnly, Category = "Runtime")
	class UGamePlayWidget* GamePlayWidget;

	UPROPERTY(VisibleAnywhere)
	int32 TotalCoins = 0;

	UPROPERTY(EditAnywhere, Category = "Components")
	int32 NumInitialFloorSurfaces = 10;

	UPROPERTY(VisibleInstanceOnly, Category = "Runtime")
	FTransform NextFloorSpawnPoint;

	UPROPERTY(VisibleInstanceOnly, Category = "Runtime")
	TArray<float> LaneSwitchValues;

	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "Delegate")
	FOnCoinsCountChanged OnCoinsCountChanged;

	AEndlessRunnerGameMode();

	UFUNCTION(BlueprintCallable)
	void CreateInitialFloorSurfaces();

	UFUNCTION(BlueprintCallable)
	class AFloorSpawn* AddFloorSurface(const bool bSpawnItems);

	UFUNCTION(BlueprintCallable)
	void AddCoin();

protected:

	virtual void BeginPlay() override;
};



