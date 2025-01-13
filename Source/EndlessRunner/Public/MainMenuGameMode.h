// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MainMenuGameMode.generated.h"

/**
 * 
 */
UCLASS()
class ENDLESSRUNNER_API AMainMenuGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditAnywhere, Category = "Components")
	TSubclassOf<class UUserWidget> MainMenuScreenClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Sound")
	class USoundWave* AmbientSounWave;


	virtual void BeginPlay() override;
};
