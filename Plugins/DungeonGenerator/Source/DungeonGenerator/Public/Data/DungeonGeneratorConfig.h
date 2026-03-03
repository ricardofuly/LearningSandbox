// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "DungeonGeneratorConfig.generated.h"

class UDungeonRoomData;
/**
 * 
 */
UCLASS()
class DUNGEONGENERATOR_API UDungeonGeneratorConfig : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
public:
	// ---- Seed ---------------------------------------------------------------
	/** Random seed. Set to 0 to use a random seed each time. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Generation")
	int32 Seed = 0;
	// ---- Room count ---------------------------------------------------------
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Generation", meta = (ClampMin = "2"))
	int32 MinRooms = 8;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Generation", meta = (ClampMin = "2"))
	int32 MaxRooms = 20;
	// ---- Room pool ----------------------------------------------------------
	/** Guaranteed start room (spawn point). Must have at least one open connector. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Rooms")
	TSoftObjectPtr<UDungeonRoomData> StartRoom;
	/** Guaranteed end room (boss / exit). Placed as far from start as possible. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Rooms")
	TSoftObjectPtr<UDungeonRoomData> EndRoom;
	/** Pool of room archetypes used to fill the dungeon. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Rooms")
	TArray<TSoftObjectPtr<UDungeonRoomData>> RoomPool;
	// ---- World placement ----------------------------------------------------
	/** World-space origin for the dungeon's start room. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Generation")
	FVector DungeonOrigin = FVector::ZeroVector;
	/** The global size of one grid tile. All rooms must align to this size to avoid overlaps. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Generation")
	FVector TileWorldSize = FVector(5000.f, 5000.f, 400.f);
};
