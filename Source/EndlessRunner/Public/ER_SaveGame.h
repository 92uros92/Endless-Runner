// Permission to use, copy, modify, and/or distribute this software for any purpose with or without fee is hereby granted.

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
