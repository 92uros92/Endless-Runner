// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HighScoreWidget.generated.h"

/**
 * 
 */
UCLASS()
class ENDLESSRUNNER_API UHighScoreWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:

	UFUNCTION(BlueprintCallable)
	void InitializeWidget(class AEndlessRunnerGameMode* RunGameMode);

	UFUNCTION(BlueprintCallable)
	void SetHighScoreCountt(int32 Count);

protected:

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* HighScoreCount;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UButton* MainMenuButton;

	UPROPERTY(BlueprintReadOnly)
	class AEndlessRunnerGameMode* ERGameMode;


	virtual void NativeConstruct() override;

	UFUNCTION()
	void OnMainMenuButtonClick();
};
