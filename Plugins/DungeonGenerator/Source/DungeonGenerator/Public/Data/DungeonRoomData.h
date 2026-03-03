// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "DungeonRoomData.generated.h"

/**
 * 
 */
UCLASS()
class DUNGEONGENERATOR_API UDungeonRoomData : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
public:
	/** The sub-level that contains this room's geometry, actors, etc. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Room")
	TSoftObjectPtr<UWorld> RoomLevel;
	/** Room footprint in grid tiles (1 tile = TileWorldSize cm) */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Room")
	FIntPoint RoomSize = FIntPoint(1, 1);
	/** How large one tile is in world-space (cm). Must match the sub-level layout. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Room")
	FVector TileWorldSize = FVector(2000.f, 2000.f, 400.f);
	/** Which sides of this tile expose doorway connectors (bitmask). */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Room",
		meta = (Bitmask, BitmaskEnum = "/Script/DungeonGenerator.EDungeonDirection"))
	int32 ConnectionFlags = 0;
	/** Tags used for filtering (e.g. "Dungeon.Room.Boss", "Dungeon.Room.Start"). */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Room")
	FGameplayTagContainer RoomTags;
	/** Weight for random selection — higher = more likely to be picked. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Room", meta = (ClampMin = "0.01"))
	float SelectionWeight = 1.f;
};
