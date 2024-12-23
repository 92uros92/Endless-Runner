// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ER_Character.generated.h"

UCLASS()
class ENDLESSRUNNER_API AER_Character : public ACharacter
{
	GENERATED_BODY()

public:

	AER_Character();

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


protected:

	virtual void BeginPlay() override;

public:	


};
