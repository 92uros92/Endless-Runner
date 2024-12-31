// Fill out your copyright notice in the Description page of Project Settings.


#include "PauseMenuWidget.h"
#include "../EndlessRunnerGameMode.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"




void UPauseMenuWidget::NativeConstruct()
{
	if (ContinueButton)
	{
		ContinueButton->OnClicked.AddDynamic(this, &UPauseMenuWidget::OnContinueClick);
	}

	if (RestartButton)
	{
		RestartButton->OnClicked.AddDynamic(this, &UPauseMenuWidget::OnRestartClick);
	}
}

void UPauseMenuWidget::OnContinueClick()
{
	UGameplayStatics::SetGamePaused(GetWorld(), false);
	RemoveFromParent();
}

void UPauseMenuWidget::OnRestartClick()
{
	UKismetSystemLibrary::ExecuteConsoleCommand(GetWorld(), TEXT("RestartLevel"));
}
