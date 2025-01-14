// Permission to use, copy, modify, and/or distribute this software for any purpose with or without fee is hereby granted.


#include "GameOverWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"



void UGameOverWidget::NativeConstruct()
{
	if (MainMenuButton)
	{
		MainMenuButton->OnClicked.AddDynamic(this, &UGameOverWidget::OnMainMenuClick);
	}

	if (RestartButton)
	{
		RestartButton->OnClicked.AddDynamic(this, &UGameOverWidget::OnRestartClick);
	}
}

void UGameOverWidget::OnMainMenuClick()
{
	UWorld* World = GetWorld();

	if (World)
	{
		UGameplayStatics::OpenLevel(World, TEXT("MainMenu"));
	}
}

void UGameOverWidget::OnRestartClick()
{
	UWorld* World = GetWorld();

	if (World)
	{
		UKismetSystemLibrary::ExecuteConsoleCommand(World, TEXT("RestartLevel"));
	}
}

