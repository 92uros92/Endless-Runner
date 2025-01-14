// Permission to use, copy, modify, and/or distribute this software for any purpose with or without fee is hereby granted.

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
