// Permission to use, copy, modify, and/or distribute this software for any purpose with or without fee is hereby granted.

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

	UFUNCTION(BlueprintCallable)
	void SetLivesCount(const int32 Count);

protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<class UUserWidget> PauseMenuWidgetClass;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* CoinsCount;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* LivesCount;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UButton* PauseButton;


	UFUNCTION()
	void OnPauseClick();

	virtual void NativeConstruct() override;
};
