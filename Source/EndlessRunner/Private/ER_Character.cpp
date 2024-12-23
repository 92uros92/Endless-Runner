// Fill out your copyright notice in the Description page of Project Settings.


#include "ER_Character.h"



AER_Character::AER_Character()
{
	PrimaryActorTick.bCanEverTick = true;

}

void AER_Character::BeginPlay()
{
	Super::BeginPlay();
	
}

void AER_Character::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AER_Character::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

