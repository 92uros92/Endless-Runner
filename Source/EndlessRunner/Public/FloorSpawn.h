// Permission to use, copy, modify, and/or distribute this software for any purpose with or without fee is hereby granted.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FloorSpawn.generated.h"


class ABaseObstacle;
class ACoinPickup;

UCLASS()
class ENDLESSRUNNER_API AFloorSpawn : public AActor
{
	GENERATED_BODY()
	
public:	

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components")
	TSubclassOf<ABaseObstacle> YellowObstacleClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components")
	TSubclassOf<ABaseObstacle> BlueObstacleClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components")
	TSubclassOf<ACoinPickup> CoinPickupClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class USceneComponent* SceneComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class UStaticMeshComponent* AsphaltComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class UStaticMeshComponent* LeftRoadMarkingComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class UStaticMeshComponent* RightRoadMarkingComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class UStaticMeshComponent* LeftCurbComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class UStaticMeshComponent* RightCurbComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class UArrowComponent* AttachPoint;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UArrowComponent* CenterLane;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UArrowComponent* RightLane;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UArrowComponent* LeftLane;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class UBoxComponent* FloorSpawnBox;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	float SpawnPercent1 = 0.1f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	float SpawnPercent2 = 0.4f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	float SpawnPercent3 = 0.7f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	float SpawnPercent4 = 0.8f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<AActor*> ChildActors;

	UPROPERTY(VisibleAnywhere)
	TArray<AFloorSpawn*> FloorSurfaces;


	AFloorSpawn();

	const FTransform& GetAttachTransform() const;

	UFUNCTION(BlueprintCallable)
	void SpawnItems();

	UFUNCTION(BlueprintCallable)
	void DestroyFloorSurface();



protected:

	UPROPERTY(VisibleInstanceOnly)
	class AEndlessRunnerGameMode* RunGameMode;

	UPROPERTY(VisibleInstanceOnly)
	FTimerHandle DestroyHandle;


	virtual void BeginPlay() override;

	UFUNCTION()
	void OnFloorSpawnBoxOverlap(UPrimitiveComponent* OverlappedComponent, 
		AActor* OtherActor, 
		UPrimitiveComponent* OtherComp, 
		int32 OtherBodyIndex, 
		bool bFromSweep, 
		const FHitResult& SweepResult);

	UFUNCTION()
	void SpawnLaneItem(UArrowComponent* Lane, int32& BigObstacle);

};
