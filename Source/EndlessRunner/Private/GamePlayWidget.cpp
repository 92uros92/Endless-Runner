// Fill out your copyright notice in the Description page of Project Settings.


#include "GamePlayWidget.h"
#include "../EndlessRunnerGameMode.h"
#include "Components/TextBlock.h"



void UGamePlayWidget::InitializeWidget(AEndlessRunnerGameMode* RunGameMode)
{
	if (RunGameMode)
	{
		CoinsCount->SetText(FText::AsNumber(0));

		RunGameMode->OnCoinsCountChanged.AddDynamic(this, &UGamePlayWidget::SetCoinsCount);
	}
}

void UGamePlayWidget::SetCoinsCount(const int32 Count)
{
	CoinsCount->SetText(FText::AsNumber(Count));
}
