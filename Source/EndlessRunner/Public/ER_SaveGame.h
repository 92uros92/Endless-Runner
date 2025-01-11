// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "ER_SaveGame.generated.h"

/**
 * 
 */
UCLASS()
class ENDLESSRUNNER_API UER_SaveGame : public USaveGame
{
	GENERATED_BODY()
	
public:

	UER_SaveGame();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Score")
	int32 HighScore;

};
