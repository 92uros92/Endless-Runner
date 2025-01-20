// Permission to use, copy, modify, and/or distribute this software for any purpose with or without fee is hereby granted.


#include "MainMenuWidget.h"
#include "Components/Button.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"



void UMainMenuWidget::NativeConstruct()
{
	if (StartButton)
	{
		StartButton->OnClicked.AddDynamic(this, &UMainMenuWidget::OnStartClick);
	}

	if (HighScoreButton)
	{
		HighScoreButton->OnClicked.AddDynamic(this, &UMainMenuWidget::OnHighScoreClick);
	}

	if (ExitButton)
	{
		ExitButton->OnClicked.AddDynamic(this, &UMainMenuWidget::OnExitClick);
	}
}

void UMainMenuWidget::OnStartClick()
{
	UWorld* World = GetWorld();

	if (World)
	{
		UGameplayStatics::OpenLevel(World, TEXT("EndlessRunnerMap"));
	}
}

void UMainMenuWidget::OnHighScoreClick()
{
	if (IsValid(this))
	{
		this->RemoveFromParent();
	}

	if (IsValid(HighScoreWidgetClass))
	{
		UUserWidget* Widget = CreateWidget(GetWorld(), HighScoreWidgetClass);

		if (Widget)
		{
			Widget->AddToViewport();
		}
	}
}

void UMainMenuWidget::OnExitClick()
{
	UWorld* World = GetWorld();

	if (World)
	{
		UKismetSystemLibrary::ExecuteConsoleCommand(World, TEXT("quit"));
	}
}

