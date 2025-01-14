// Permission to use, copy, modify, and/or distribute this software for any purpose with or without fee is hereby granted.


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

	if (MainMenuButton)
	{
		MainMenuButton->OnClicked.AddDynamic(this, &UPauseMenuWidget::OnMainMenuClick);
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

void UPauseMenuWidget::OnMainMenuClick()
{
	UWorld* World = GetWorld();

	if (World)
	{
		UGameplayStatics::OpenLevel(World, TEXT("MainMenu"));
	}
}
