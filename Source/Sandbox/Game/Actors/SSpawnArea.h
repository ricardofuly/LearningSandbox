// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SSpawnArea.generated.h"

class USplineComponent;

UCLASS()
class SANDBOX_API ASSpawnArea : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ASSpawnArea();
	
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	virtual void OnConstruction(const FTransform& Transform) override;

	/* ================= COMPONENTS ================= */

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
	USplineComponent* Spline;

	/* ================= CONFIG ================= */

	UPROPERTY(EditAnywhere, Category="Spawn")
	TSubclassOf<AActor> PlayerStartClass;

	UPROPERTY(EditAnywhere, Category="Spawn", meta=(ClampMin="0"))
	int32 MaxSpawnPoints = 10;

	UPROPERTY(EditAnywhere, Category="Spawn", meta=(ClampMin="0"))
	float MinDistanceBetweenSpawns = 300.f;

	UPROPERTY(EditAnywhere, Category="Spawn", meta=(ClampMin="0"))
	float MaxHeightOffset = 500.f;

	UPROPERTY(EditAnywhere, Category="Spawn", meta=(ClampMin="0"))
	float TraceHeight = 2000.f;

	UPROPERTY(EditAnywhere, Category="Spawn", meta=(ClampMin="0"))
	float CollisionRadius = 50.f;

	UPROPERTY(EditAnywhere, Category="Debug")
	bool bDrawDebug = true;

	/* ================= INTERNAL ================= */

	UPROPERTY(Transient)
	TArray<FVector> ValidSpawnPoints;

	UPROPERTY(Transient)
	TArray<AActor*> SpawnedPlayerStarts;

	/* ================= LOGIC ================= */
};
