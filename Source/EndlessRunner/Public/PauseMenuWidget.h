// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PauseMenuWidget.generated.h"

/**
 * 
 */
UCLASS()
class ENDLESSRUNNER_API UPauseMenuWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UButton* ContinueButton;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* RestartButton;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* MainMenuButton;


	UFUNCTION()
	void OnContinueClick();

	UFUNCTION()
	void OnRestartClick();

	UFUNCTION()
	void OnMainMenuClick();

	virtual void NativeConstruct() override;

};
