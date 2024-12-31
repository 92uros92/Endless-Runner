// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GamePlayWidget.generated.h"

/**
 * 
 */
UCLASS()
class ENDLESSRUNNER_API UGamePlayWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:

	UFUNCTION(BlueprintCallable)
	void InitializeWidget(class AEndlessRunnerGameMode* RunGameMode);

	UFUNCTION(BlueprintCallable)
	void SetCoinsCount(const int32 Count);

protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<class UUserWidget> PauseMenuWidgetClass;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* CoinsCount;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UButton* PauseButton;


	UFUNCTION()
	void OnPauseClick();

	virtual void NativeConstruct() override;
};
