// Fill out your copyright notice in the Description page of Project Settings.


#include "ER_Character.h"
#include "../EndlessRunnerGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/Controller.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Components/InputComponent.h"



AER_Character::AER_Character()
{
	PrimaryActorTick.bCanEverTick = true;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->bUsePawnControlRotation = true;
	SpringArm->SetupAttachment(RootComponent);

	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));
	SpringArm->bUsePawnControlRotation = false;
	CameraComp->SetupAttachment(SpringArm, USpringArmComponent::SocketName);
	
	CurrentLane = 1;
	NextLane = 0;
}

void AER_Character::BeginPlay()
{
	Super::BeginPlay();
	
	RunGameMode = Cast<AEndlessRunnerGameMode>(UGameplayStatics::GetGameMode(GetWorld()));

	check(RunGameMode);

	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(ERMappingContext, 0);
		}
	}
}

void AER_Character::UpdateChangeLane(const float Value)
{
	FVector Location = GetCapsuleComponent()->GetComponentLocation();
	Location.Y = FMath::Lerp(RunGameMode->LaneSwitchValues[CurrentLane], RunGameMode->LaneSwitchValues[NextLane], Value);
	SetActorLocation(Location);
}

void AER_Character::FinishedChangeLane()
{
	CurrentLane = NextLane;
}

void AER_Character::MoveRight()
{
	NextLane = FMath::Clamp(CurrentLane + 1, 0, 2);
	ChangeLane();
}

void AER_Character::MoveLeft()
{
	NextLane = FMath::Clamp(CurrentLane - 1, 0, 2);
	ChangeLane();
}

void AER_Character::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FRotator ControlRot = GetControlRotation();
	ControlRot.Roll = 0.0f;
	ControlRot.Pitch = 0.0f;

	AddMovementInput(ControlRot.Vector());
}

void AER_Character::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		EnhancedInputComponent->BindAction(MoveRightAction, ETriggerEvent::Triggered, this, &AER_Character::MoveRight);
		EnhancedInputComponent->BindAction(MoveLeftAction, ETriggerEvent::Triggered, this, &AER_Character::MoveLeft);
	}
}
