// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseObstacle.generated.h"


class USceneComponent;
class UStaticMeshComponent;

UCLASS()
class ENDLESSRUNNER_API ABaseObstacle : public AActor
{
	GENERATED_BODY()
	
public:	

	ABaseObstacle();

	UFUNCTION()
	void OnObstacleHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

protected:


public:	

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USceneComponent* SceneComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* MeshComp;

};
