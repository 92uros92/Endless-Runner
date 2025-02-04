// Permission to use, copy, modify, and/or distribute this software for any purpose with or without fee is hereby granted.

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
	void SetHighScoreCount(int32 Count);

protected:

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* HighScoreCount;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UButton* MainMenuButton;

	UPROPERTY(BlueprintReadOnly)
	class AEndlessRunnerGameMode* ERGameMode;

	UPROPERTY(BlueprintReadOnly)
	class UER_SaveGame* ERSaveGame;


	virtual void NativeConstruct() override;

	UFUNCTION()
	void OnMainMenuButtonClick();
};
