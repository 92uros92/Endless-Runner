// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenuGameMode.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"



void AMainMenuGameMode::BeginPlay()
{
	Super::BeginPlay();

	if (MainMenuScreenClass)
	{
		UUserWidget* Widget = CreateWidget(GetWorld(), MainMenuScreenClass);

		if (Widget)
		{
			Widget->AddToViewport();
		}

		if (AmbientSounWave)
		{
			UGameplayStatics::PlaySound2D(GetWorld(), AmbientSounWave);
		}
	}
}
