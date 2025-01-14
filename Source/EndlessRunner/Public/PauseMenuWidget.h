// Permission to use, copy, modify, and/or distribute this software for any purpose with or without fee is hereby granted.

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
