// Fill out your copyright notice in the Description page of Project Settings.


#include "HighScoreWidget.h"
#include "../EndlessRunnerGameMode.h"
#include "ER_SaveGame.h"
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

	//UWidgetBlueprintLibrary::SetInputMode_GameAndUIEx(UGameplayStatics::GetPlayerController(GetWorld(), 0), this);
}

void UHighScoreWidget::InitializeWidget(AEndlessRunnerGameMode* RunGameMode)
{
	if (RunGameMode)
	{
		RunGameMode->LoadHighScore();

		HighScoreCount->SetText(FText::AsNumber(ERSaveGame->HighScore));

		RunGameMode->OnHighScoreChanged.AddDynamic(this, &UHighScoreWidget::SetHighScoreCount);
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

void UHighScoreWidget::SetHighScoreCount(int32 Count)
{
	Count = ERSaveGame->HighScore;
	HighScoreCount->SetText(FText::AsNumber(Count));
}

