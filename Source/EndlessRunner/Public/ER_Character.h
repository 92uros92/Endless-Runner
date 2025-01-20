// Permission to use, copy, modify, and/or distribute this software for any purpose with or without fee is hereby granted.

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

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Sound")
	class USoundWave* BackgroundSounWave;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadWrite, Category = "Lane")
	int32 CurrentLane;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadWrite, Category = "Lane")
	int32 NextLane;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Speed")
	float InitialSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Speed")
	float MaxSpeed;


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

	UFUNCTION(Category = "Speed")
	void IncreseSpeed();

	UFUNCTION(Category = "Speed")
	void UpdateSpeed();

	UFUNCTION(Category = "Speed")
	void ResetSpeed();

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
	FTimerHandle ChangeSpeedTimer;

	UPROPERTY()
	class APlayerStart* PlayerStart;

	UPROPERTY()
	bool bIsDeath;

	UPROPERTY()
	bool bResetLevel;


	virtual void BeginPlay() override;

	UFUNCTION()
	void OnDeath();

	void MoveRight();

	void MoveLeft();

	UFUNCTION()
	void ResetLevel();

private:

	UPROPERTY(VisibleInstanceOnly)
	class AEndlessRunnerGameMode* RunGameMode;
};
