// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "EndlessRunnerGameMode.generated.h"


UCLASS(minimalapi)
class AEndlessRunnerGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:

	AEndlessRunnerGameMode();

	UPROPERTY(EditAnywhere, Category = "Components")
	TSubclassOf<class AFloorSpawn> FloorSpawnClass;

	UPROPERTY(EditAnywhere, Category = "Components")
	int32 NumInitialFloorSurfaces = 10;

	UPROPERTY(VisibleInstanceOnly, Category = "Runtime")
	FTransform NextFloorSpawnPoint;

	UPROPERTY(VisibleInstanceOnly, Category = "Runtime")
	TArray<float> LaneSwitchValues;


	UFUNCTION(BlueprintCallable)
	void CreateInitialFloorSurfaces();

	UFUNCTION(BlueprintCallable)
	class AFloorSpawn* AddFloorSurface(const bool bSpawnItems);

protected:

	virtual void BeginPlay() override;
};



