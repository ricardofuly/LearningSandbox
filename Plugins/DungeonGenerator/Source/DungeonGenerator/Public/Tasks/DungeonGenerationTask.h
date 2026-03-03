#pragma once

#include "CoreMinimal.h"
#include "Types/DungeonTypes.h"

class UDungeonGeneratorConfig;

class FDungeonGenerationTask
{
public:
	explicit FDungeonGenerationTask(const UDungeonGeneratorConfig* InConfig, const FTransform& StartTransform);
	
	FDungeonLayout RunGeneration();

private:
	struct FOpenConnector { FIntPoint GridPos; int32 Direction; };

	// Snapshot of config values (copied before thread starts — no UObject access on bg thread)
	int32 Seed;
	int32 MaxRooms;
	int32 MinRooms;
	FVector GlobalTileSize;
	FTransform DungeonStartTransform;
	TSet<FIntPoint> InitiallyOccupiedCells;
	
	// Lightweight snapshot: index → (Size, ConnectionFlags, TileWorldSize, Weight)
	struct FRoomSnapshot
	{
		FIntPoint  Size;
		FVector    TileWorldSize;
		int32      ConnectionFlags;
		float      Weight;
	};
	
	TArray<FRoomSnapshot> RoomSnapshots;
	int32 StartRoomIndex = 0;
	int32 EndRoomIndex   = 0;
	TFunction<void(FDungeonLayout)> OnComplete;
	
	// Internal helpers
	FDungeonLayout RunBSPExpansion();
	
	bool TryPlaceRoom(int32 RoomIndex, FIntPoint GridPos, int32 RequiredConnectionMask,
										  TSet<FIntPoint>& OccupiedCells,
										  TArray<FDungeonRoomPlacement>& OutPlacements,
										  FRandomStream& Rand,
										  bool bIsStartRoom,
										  float Rotation = 0.f) const;
	
	FVector GridToWorld(FIntPoint GridPos, int32 RoomIndex) const;
	
	static int32 RotateMask(int32 Mask, int32 Steps); // 0, 1, 2, 3 (90 deg increments)
	static int32 OppositeDirection(int32 DirMask);
};
