// Fill out your copyright notice in the Description page of Project Settings.


#include "CoinPickup.h"
#include "ER_Character.h"
#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/RotatingMovementComponent.h"
#include "Kismet/GameplayStatics.h"



ACoinPickup::ACoinPickup()
{
	SceneComp = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComp"));
	RootComponent = SceneComp;

	SphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	SphereComp->SetupAttachment(SceneComp);
	SphereComp->SetCollisionProfileName(TEXT("OverlapOnlyPawn"));

	CoinMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CoinMeshComp"));
	CoinMeshComp->SetupAttachment(SphereComp);
	CoinMeshComp->SetCollisionProfileName(TEXT("OverlapOnlyPawn"));

	RotatingMovmentComp = CreateDefaultSubobject<URotatingMovementComponent>(TEXT("RotatingMovmentComp"));
	RotatingMovmentComp->RotationRate = FRotator(0.0f, 180.0f, 0.0f);

}

void ACoinPickup::BeginPlay()
{
	Super::BeginPlay();

	SphereComp->OnComponentBeginOverlap.AddDynamic(this, &ACoinPickup::OnSphereOverlap);
}

void ACoinPickup::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AER_Character* Character = Cast<AER_Character>(OtherActor);

	if (Character)
	{
		if (PickupSound)
		{
			UGameplayStatics::PlaySoundAtLocation(GetWorld(), PickupSound, GetActorLocation());
		}

		Character->AddCoin();

		Destroy();
	}
}
