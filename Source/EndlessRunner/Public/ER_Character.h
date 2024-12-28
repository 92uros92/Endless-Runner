// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "ER_Character.generated.h"


UCLASS()
class ENDLESSRUNNER_API AER_Character : public ACharacter
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Sound")
	class USoundBase* DeathSound;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadWrite, Category = "Lane")
	int32 CurrentLane;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadWrite, Category = "Lane")
	int32 NextLane;


	AER_Character();

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintImplementableEvent, Category = "Lane")
	void ChangeLane();

	UFUNCTION(BlueprintCallable, Category = "Lane")
	void UpdateChangeLane(const float Value);

	UFUNCTION(BlueprintCallable, Category = "Lane")
	void FinishedChangeLane();

	UFUNCTION(BlueprintCallable)
	void Death();

	UFUNCTION()
	void AddCoin();

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class UCameraComponent* CameraComp;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	class UInputMappingContext* ERMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	class UInputAction* MoveRightAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	class UInputAction* MoveLeftAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputAction* JumpAction;

	UPROPERTY()
	FTimerHandle RestartTimer;

	UPROPERTY()
	bool bIsDeath;

	virtual void BeginPlay() override;

	UFUNCTION()
	void OnDeath();

	void MoveRight();

	void MoveLeft();

private:

	UPROPERTY(VisibleInstanceOnly)
	class AEndlessRunnerGameMode* RunGameMode;
};
