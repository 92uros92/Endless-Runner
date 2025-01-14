// Permission to use, copy, modify, and/or distribute this software for any purpose with or without fee is hereby granted.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainMenuWidget.generated.h"

/**
 * 
 */
UCLASS()
class ENDLESSRUNNER_API UMainMenuWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<class UUserWidget> HighScoreWidgetClass;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UButton* StartButton;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UButton* HighScoreButton;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UButton* ExitButton;


	UFUNCTION()
	void OnStartClick();

	UFUNCTION()
	void OnHighScoreClick();

	UFUNCTION()
	void OnExitClick();

	virtual void NativeConstruct() override;

};
