// Fill out your copyright notice in the Description page of Project Settings.


#include "HighScoreWidget.h"
#include "../EndlessRunnerGameMode.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"



void UHighScoreWidget::NativeConstruct()
{
	if (MainMenuButton)
	{
		MainMenuButton->OnClicked.AddDynamic(this, &UHighScoreWidget::OnMainMenuButtonClick);
	}

	UWidgetBlueprintLibrary::SetInputMode_GameAndUIEx(UGameplayStatics::GetPlayerController(GetWorld(), 0), this);
}

void UHighScoreWidget::InitializeWidget(AEndlessRunnerGameMode* RunGameMode)
{
	if (RunGameMode)
	{
		HighScoreCount->SetText(FText::AsNumber(0));

		RunGameMode->OnCoinsCountChanged.AddDynamic(this, &UHighScoreWidget::SetHighScoreCountt);
	}
}

void UHighScoreWidget::OnMainMenuButtonClick()
{
	UWorld* World = GetWorld();

	if (World)
	{
		UGameplayStatics::OpenLevel(World, TEXT("MainMenu"));
	}
}

void UHighScoreWidget::SetHighScoreCountt(int32 Count)
{
	Count = ERGameMode->HighScore;
	HighScoreCount->SetText(FText::AsNumber(Count));
}

