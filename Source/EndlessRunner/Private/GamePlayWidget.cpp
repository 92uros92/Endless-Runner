// Fill out your copyright notice in the Description page of Project Settings.


#include "GamePlayWidget.h"
#include "../EndlessRunnerGameMode.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"




void UGamePlayWidget::NativeConstruct()
{
	if (PauseButton)
	{
		PauseButton->OnClicked.AddDynamic(this, &UGamePlayWidget::OnPauseClick);
	}

	UWidgetBlueprintLibrary::SetInputMode_GameAndUIEx(UGameplayStatics::GetPlayerController(GetWorld(), 0), this);
}

void UGamePlayWidget::InitializeWidget(AEndlessRunnerGameMode* RunGameMode)
{
	if (RunGameMode)
	{
		CoinsCount->SetText(FText::AsNumber(0));
		LivesCount->SetText(FText::AsNumber(RunGameMode->MaxLives));

		RunGameMode->OnCoinsCountChanged.AddDynamic(this, &UGamePlayWidget::SetCoinsCount);
		RunGameMode->OnLivesCountChanged.AddDynamic(this, &UGamePlayWidget::SetLivesCount);
	}
}

void UGamePlayWidget::SetCoinsCount(const int32 Count)
{
	CoinsCount->SetText(FText::AsNumber(Count));
}

void UGamePlayWidget::SetLivesCount(const int32 Count)
{
	LivesCount->SetText(FText::AsNumber(Count));
}

void UGamePlayWidget::OnPauseClick()
{
	if (IsValid(PauseMenuWidgetClass))
	{
		UGameplayStatics::SetGamePaused(GetWorld(), true);

		UUserWidget* Widget = CreateWidget(GetWorld(), PauseMenuWidgetClass);

		if (Widget)
		{
			Widget->AddToViewport();
		}
	}
}
