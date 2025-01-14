// Permission to use, copy, modify, and/or distribute this software for any purpose with or without fee is hereby granted.


#include "BaseObstacle.h"
#include "ER_Character.h"
#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"



ABaseObstacle::ABaseObstacle()
{
	SceneComp = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComp"));
	RootComponent = SceneComp;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	MeshComp->SetupAttachment(SceneComp);

	MeshComp->OnComponentHit.AddDynamic(this, &ABaseObstacle::OnObstacleHit);
}

void ABaseObstacle::OnObstacleHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	AER_Character* Character = Cast<AER_Character>(OtherActor);

	if (Character)
	{
		Character->Death();
	}
}
