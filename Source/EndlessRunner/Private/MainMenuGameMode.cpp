// Permission to use, copy, modify, and/or distribute this software for any purpose with or without fee is hereby granted.


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
