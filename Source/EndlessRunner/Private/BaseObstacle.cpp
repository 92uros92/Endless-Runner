// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseObstacle.h"
#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"



ABaseObstacle::ABaseObstacle()
{
	SceneComp = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComp"));
	RootComponent = SceneComp;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	MeshComp->SetupAttachment(SceneComp);

}
