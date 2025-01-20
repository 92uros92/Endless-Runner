// Permission to use, copy, modify, and/or distribute this software for any purpose with or without fee is hereby granted.


#include "ER_Character.h"
#include "../EndlessRunnerGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/Controller.h"
#include "Sound/SoundBase.h"
#include "GameFramework/PlayerStart.h"
#include "GameFramework/CharacterMovementComponent.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Components/InputComponent.h"



AER_Character::AER_Character()
{
	PrimaryActorTick.bCanEverTick = true;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->TargetArmLength = 450.0f;
	SpringArm->SocketOffset = FVector(0.0f, 0.0f, 150.0f);
	SpringArm->bUsePawnControlRotation = true;
	SpringArm->SetupAttachment(RootComponent);

	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));
	CameraComp->bUsePawnControlRotation = false;
	CameraComp->SetupAttachment(SpringArm, USpringArmComponent::SocketName);
	
	GetCharacterMovement()->MaxWalkSpeed = InitialSpeed;
	InitialSpeed = 450.0f;
	MaxSpeed = 1950.0f;

	CurrentLane = 1;
	NextLane = 0;

	bIsDeath = false;
	bResetLevel = false;
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

	if (BackgroundSounWave)
	{
		UGameplayStatics::PlaySound2D(GetWorld(), BackgroundSounWave);
	}

	RunGameMode->OnLevelReset.AddDynamic(this, &AER_Character::ResetLevel);

	PlayerStart = Cast<APlayerStart>(UGameplayStatics::GetActorOfClass(GetWorld(), APlayerStart::StaticClass()));

	IncreseSpeed();
}

void AER_Character::UpdateChangeLane(const float Value)
{
	// Change location on the lane
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

void AER_Character::ResetLevel()
{
	if (RestartTimer.IsValid())
	{
		GetWorld()->GetTimerManager().ClearTimer(RestartTimer);
	}

	if (ChangeSpeedTimer.IsValid())
	{
		GetWorld()->GetTimerManager().ClearTimer(ChangeSpeedTimer);
	}

	bIsDeath = false;
	bResetLevel = true;
	EnableInput(nullptr);
	GetMesh()->SetVisibility(true);

	if (PlayerStart)
	{
		SetActorLocation(PlayerStart->GetActorLocation());
		SetActorRotation(PlayerStart->GetActorRotation());
	}

	ResetSpeed();
}

void AER_Character::OnDeath()
{
	if (RestartTimer.IsValid())
	{
		GetWorld()->GetTimerManager().ClearTimer(RestartTimer);
	}

	if (ChangeSpeedTimer.IsValid())
	{
		GetWorld()->GetTimerManager().ClearTimer(ChangeSpeedTimer);
	}

	bResetLevel = true;

	RunGameMode->PlayerDied();
}

void AER_Character::Death()
{
	if (!bIsDeath)
	{
		//UE_LOG(LogTemp, Warning, TEXT("Character DIED!!"));

		bResetLevel = true;

		const FVector Location = GetActorLocation();

		UWorld* World = GetWorld();

		if (World)
		{
			bIsDeath = true;
			DisableInput(nullptr);

			if (DeathSound)
			{
				UGameplayStatics::PlaySoundAtLocation(World, DeathSound, Location);
			}

			GetMesh()->SetVisibility(false);

			if (!GetWorldTimerManager().IsTimerActive(RestartTimer))
			{
				// Call OnDeath function every second
				World->GetTimerManager().SetTimer(RestartTimer, this, &AER_Character::OnDeath, 1.0f);
			}
		}
	}
}

void AER_Character::AddCoin()
{
	RunGameMode->AddCoin();
}

void AER_Character::IncreseSpeed()
{
	UWorld* World = GetWorld();

	if (World)
	{
		if (!GetWorldTimerManager().IsTimerActive(ChangeSpeedTimer))
		{
			// After 10 seconds from the start call UpdateSpeed function and then calls it every 10 seconds
			World->GetTimerManager().SetTimer(ChangeSpeedTimer, this, &AER_Character::UpdateSpeed, 10.0f, true, 10.0f);
		}

		//UE_LOG(LogTemp, Warning, TEXT("(IncreseSpeed()) Initial Speed: %f"), InitialSpeed);
	}
}

void AER_Character::UpdateSpeed()
{
	if (InitialSpeed < MaxSpeed)
	{
		float NewInitialSpeed = InitialSpeed + 300.0f;

		InitialSpeed = NewInitialSpeed;

		GetCharacterMovement()->MaxWalkSpeed = NewInitialSpeed;

		UE_LOG(LogTemp, Warning, TEXT("(UpdateSpeed()) NewInitial Speed: %f"), NewInitialSpeed);
	}
}

void AER_Character::ResetSpeed()
{
	if (bResetLevel)
	{
		UWorld* World = GetWorld();

		if (World)
		{
			float ResetInitialSpeed = 450.0f;
			InitialSpeed = ResetInitialSpeed;
			GetCharacterMovement()->MaxWalkSpeed = ResetInitialSpeed;

			if (!GetWorldTimerManager().IsTimerActive(ChangeSpeedTimer))
			{
				World->GetTimerManager().SetTimer(ChangeSpeedTimer, this, &AER_Character::UpdateSpeed, 10.0f, true, 10.0f);

				UE_LOG(LogTemp, Warning, TEXT("(UpdateSpeed()) ResetInitialSpeed Speed: %f"), ResetInitialSpeed);
			}
		}
	}
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
