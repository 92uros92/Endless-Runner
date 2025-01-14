// Permission to use, copy, modify, and/or distribute this software for any purpose with or without fee is hereby granted.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameOverWidget.generated.h"

/**
 * 
 */
UCLASS()
class ENDLESSRUNNER_API UGameOverWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UButton* MainMenuButton;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UButton* RestartButton;


	UFUNCTION()
	void OnMainMenuClick();

	UFUNCTION()
	void OnRestartClick();

	virtual void NativeConstruct() override;

};
