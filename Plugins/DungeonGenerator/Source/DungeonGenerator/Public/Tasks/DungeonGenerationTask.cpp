#include "DungeonGenerationTask.h"

#include "Data/DungeonGeneratorConfig.h"
#include "Data/DungeonRoomData.h"

class UDungeonRoomData;

FDungeonGenerationTask::FDungeonGenerationTask(const UDungeonGeneratorConfig* InConfig, const FTransform& StartTransform)
{
	check(IsInGameThread());
	check(InConfig);
	
	Seed        = (InConfig->Seed == 0) ? FMath::Rand() : InConfig->Seed;
	MinRooms    = InConfig->MinRooms;
	MaxRooms    = InConfig->MaxRooms;
	GlobalTileSize = InConfig->TileWorldSize;
	DungeonStartTransform = StartTransform;
	
	// Scan the world for existing geometry to avoid overlaps
	UWorld* World = nullptr;
	if (InConfig->GetOuter()) World = InConfig->GetWorld();
	
	if (World)
	{
		const float ScanCellSize = 500.f; // Adjust based on expected room scale
		const int32 ScanRange = 20; // Cells around start
		
		FCollisionQueryParams Params;
		Params.AddIgnoredActor(World->GetFirstPlayerController() ? World->GetFirstPlayerController()->GetPawn() : nullptr);

		for (int32 X = -ScanRange; X <= ScanRange; ++X)
		{
			for (int32 Y = -ScanRange; Y <= ScanRange; ++Y)
			{
				FVector ScanPos = GridToWorld(FIntPoint(X, Y), INDEX_NONE); // RoomIndex doesn't matter for origin-based grid
				
				// Perform overlap check
				if (World->OverlapAnyTestByChannel(ScanPos + FVector(0,0,50), FQuat::Identity, ECC_WorldStatic, FCollisionShape::MakeBox(FVector(ScanCellSize*0.4f)), Params))
				{
					InitiallyOccupiedCells.Add(FIntPoint(X, Y));
				}
			}
		}
	}
	
	// Helper lambda to snapshot one room data asset
	auto SnapshotRoom = [&](const auto& SoftPtr) -> int32
	{
		UDungeonRoomData* Data = SoftPtr.LoadSynchronous(); // safe on game thread
		if (!Data) return INDEX_NONE;
		FRoomSnapshot Snap;
		Snap.Size          = Data->RoomSize;
		Snap.TileWorldSize = Data->TileWorldSize;
		Snap.ConnectionFlags = Data->ConnectionFlags;
		Snap.Weight        = FMath::Max(Data->SelectionWeight, 0.01f);
		RoomSnapshots.Add(Snap);
		return RoomSnapshots.Num() - 1;
	};
	
	// Index 0 = Start, Index 1 = End, then pool
	StartRoomIndex = SnapshotRoom(InConfig->StartRoom);
	EndRoomIndex   = SnapshotRoom(InConfig->EndRoom);
	for (const auto& RoomPtr : InConfig->RoomPool)
	{
		SnapshotRoom(RoomPtr);
	}
}

FDungeonLayout FDungeonGenerationTask::RunGeneration()
{
	return RunBSPExpansion();
}

FDungeonLayout FDungeonGenerationTask::RunBSPExpansion()
{
	FDungeonLayout Layout;
    if (StartRoomIndex == INDEX_NONE || EndRoomIndex == INDEX_NONE || RoomSnapshots.Num() < 2)
    {
        Layout.bSuccess = false;
        Layout.ErrorMessage = TEXT("Invalid config: missing Start or End room.");
        return Layout;
    }

    FRandomStream Rand(Seed);
    TSet<FIntPoint> OccupiedCells = InitiallyOccupiedCells;
    TArray<FDungeonRoomPlacement> Placements;
    TArray<FOpenConnector> ExhaustedConnectors;

    // --- Place start room at origin ---
    if (!TryPlaceRoom(StartRoomIndex, FIntPoint(0, 0), 0, OccupiedCells, Placements, Rand, true))
    {
        Layout.bSuccess = false;
        Layout.ErrorMessage = TEXT("Failed to place start room (blocked by world geometry).");
        return Layout;
    }

    // --- Open frontier ---
    TArray<FOpenConnector> Frontier;

    auto AddToFrontier = [&](const FDungeonRoomPlacement& Room)
    {
        if (Room.ConnectionMask & (int32)EDungeonDirection::North) Frontier.Add({ Room.GridPos + FIntPoint(0,  1), (int32)EDungeonDirection::South });
        if (Room.ConnectionMask & (int32)EDungeonDirection::South) Frontier.Add({ Room.GridPos + FIntPoint(0, -1), (int32)EDungeonDirection::North });
        if (Room.ConnectionMask & (int32)EDungeonDirection::East)  Frontier.Add({ Room.GridPos + FIntPoint( 1, 0), (int32)EDungeonDirection::West  });
        if (Room.ConnectionMask & (int32)EDungeonDirection::West)  Frontier.Add({ Room.GridPos + FIntPoint(-1, 0), (int32)EDungeonDirection::East  });
    };

    AddToFrontier(Placements[0]);

    const int32 TargetRooms = Rand.RandRange(MinRooms, MaxRooms);
    while (Placements.Num() < TargetRooms - 1 && Frontier.Num() > 0)
    {
        const int32 FrontierIdx = Rand.RandRange(0, Frontier.Num() - 1);
        FOpenConnector Connector = Frontier[FrontierIdx];
        Frontier.RemoveAtSwap(FrontierIdx);

        if (OccupiedCells.Contains(Connector.GridPos))
        {
            ExhaustedConnectors.Add(Connector);
            continue;
        }

        TArray<float> Weights;
        TArray<int32> CandidateRoomIndices;
        float TotalWeight = 0.f;

        for (int32 i = 2; i < RoomSnapshots.Num(); ++i)
        {
            if (RoomSnapshots[i].ConnectionFlags & Connector.Direction)
            {
                Weights.Add(RoomSnapshots[i].Weight);
                CandidateRoomIndices.Add(i);
                TotalWeight += RoomSnapshots[i].Weight;
            }
        }

        if (TotalWeight <= 0.f)
        {
            ExhaustedConnectors.Add(Connector);
            continue;
        }

        float Pick = Rand.FRandRange(0.f, TotalWeight);
        int32 ChosenIdx = INDEX_NONE;
        for (int32 i = 0; i < Weights.Num(); ++i)
        {
            Pick -= Weights[i];
            if (Pick <= 0.f) { ChosenIdx = CandidateRoomIndices[i]; break; }
        }

        if (ChosenIdx == INDEX_NONE) continue;

        // --- NEW: Try all 4 rotations for the chosen room ---
        bool bPlaced = false;
        TArray<int32> Rotations = {0, 1, 2, 3};
        // Shuffling rotations here could add variety, but starting at 0 is safer for performance
        
        for (int32 RotSteps : Rotations)
        {
            if (TryPlaceRoom(ChosenIdx, Connector.GridPos, Connector.Direction, OccupiedCells, Placements, Rand, false, RotSteps * 90.f))
            {
                AddToFrontier(Placements.Last());
                bPlaced = true;
                break;
            }
        }

        if (!bPlaced)
        {
            ExhaustedConnectors.Add(Connector);
        }
    }

    // --- Place end room at the farthest reachable point ---
    TArray<FOpenConnector> EndCandidates = Frontier;
    EndCandidates.Append(ExhaustedConnectors);

    float MaxDist = -1.f;
    FOpenConnector BestConnector;
	BestConnector.GridPos = FIntPoint::ZeroValue;
	BestConnector.Direction = 0;

    for (const FOpenConnector& C : EndCandidates)
    {
        if (!OccupiedCells.Contains(C.GridPos) && (RoomSnapshots[EndRoomIndex].ConnectionFlags & C.Direction))
        {
            const float D = FVector2f(C.GridPos.X, C.GridPos.Y).Length();
            if (D > MaxDist)
            {
                MaxDist = D;
                BestConnector = C;
            }
        }
    }

    if (MaxDist >= 0.f)
    {
        if (TryPlaceRoom(EndRoomIndex, BestConnector.GridPos, BestConnector.Direction, OccupiedCells, Placements, Rand, false))
        {
            // Successfully placed end room, remove its connector from candidate lists
            Frontier.RemoveAll([&](const FOpenConnector& C){ return C.GridPos == BestConnector.GridPos; });
            ExhaustedConnectors.RemoveAll([&](const FOpenConnector& C){ return C.GridPos == BestConnector.GridPos; });
        }
    }

    // --- CAPPING PASS: Fill remaining open doors with 1-way "dead end" rooms ---
    TArray<FOpenConnector> RemainingOpen = Frontier;
    for (const FOpenConnector& Connector : RemainingOpen)
    {
        if (OccupiedCells.Contains(Connector.GridPos)) continue;

        // Find any 1-way room in the pool that matches the required entrance direction
        for (int32 i = 2; i < RoomSnapshots.Num(); ++i)
        {
            const FRoomSnapshot& Snap = RoomSnapshots[i];
            
            // Check if it's a 1-way room (only one bit set in ConnectionFlags)
            bool bIsOneWay = (Snap.ConnectionFlags != 0) && ((Snap.ConnectionFlags & (Snap.ConnectionFlags - 1)) == 0);
            
            if (bIsOneWay)
            {
                // Try all rotations (one of them will definitely have the door facing our neighbor)
                bool bCapped = false;
                for (int32 Rot : {0, 1, 2, 3})
                {
                    if (TryPlaceRoom(i, Connector.GridPos, Connector.Direction, OccupiedCells, Placements, Rand, false, Rot * 90.f))
                    {
                        bCapped = true;
                        break;
                    }
                }
                if (bCapped) break;
            }
        }
    }

    Layout.Rooms    = MoveTemp(Placements);
    Layout.bSuccess = (Layout.Rooms.Num() >= MinRooms);
    if (!Layout.bSuccess)
        Layout.ErrorMessage = FString::Printf(TEXT("Generated only %d/min %d rooms. Try clear the path!"), Layout.Rooms.Num(), MinRooms);

    return Layout;
}

bool FDungeonGenerationTask::TryPlaceRoom(int32 RoomIndex, FIntPoint GridPos, int32 RequiredConnectionMask,
	TSet<FIntPoint>& OccupiedCells, TArray<FDungeonRoomPlacement>& OutPlacements, FRandomStream& Rand,
	bool bIsStartRoom, float Rotation) const
{
	if (RoomIndex == INDEX_NONE) return false;
	const FRoomSnapshot& RoomSnap = RoomSnapshots[RoomIndex];

	// Calculate rotated size
	int32 RotSteps = FMath::RoundToInt(Rotation / 90.f) % 4;
	int32 SizeX = RoomSnap.Size.X;
	int32 SizeY = RoomSnap.Size.Y;
	if (RotSteps % 2 != 0) Swap(SizeX, SizeY);

	// Check if ALL required cells are free
	for (int32 X = 0; X < SizeX; ++X)
	{
		for (int32 Y = 0; Y < SizeY; ++Y)
		{
			if (OccupiedCells.Contains(GridPos + FIntPoint(X, Y)))
			{
				return false;
			}
		}
	}

	int32 RotatedMask = RotateMask(RoomSnap.ConnectionFlags, RotSteps);

	// --- NEW: Strict Adjacency Check ---
	// For every tile this room occupies, check all 4 neighbors
	for (int32 X = 0; X < SizeX; ++X)
	{
		for (int32 Y = 0; Y < SizeY; ++Y)
		{
			FIntPoint CurrentCell = GridPos + FIntPoint(X, Y);
			TArray<TPair<FIntPoint, EDungeonDirection>> Neighbors = {
				{CurrentCell + FIntPoint(0, 1),  EDungeonDirection::North},
				{CurrentCell + FIntPoint(0, -1), EDungeonDirection::South},
				{CurrentCell + FIntPoint(1, 0),  EDungeonDirection::East},
				{CurrentCell + FIntPoint(-1, 0), EDungeonDirection::West}
			};

			for (auto& Neighbor : Neighbors)
			{
				// Find if a room is already placed in this neighbor cell
				const FDungeonRoomPlacement* ExistingNeighbor = nullptr;
				for (const auto& P : OutPlacements)
				{
					// A multi-tile room might block multiple cells, we need to check if neighbor coord is within its bounds
					const FRoomSnapshot& NeighborSnap = RoomSnapshots[P.RoomDataIndex];
					int32 NX = NeighborSnap.Size.X;
					int32 NY = NeighborSnap.Size.Y;
					int32 NRotSteps = FMath::RoundToInt(P.Rotation / 90.f) % 4;
					if (NRotSteps % 2 != 0) Swap(NX, NY);

					if (Neighbor.Key.X >= P.GridPos.X && Neighbor.Key.X < P.GridPos.X + NX &&
						Neighbor.Key.Y >= P.GridPos.Y && Neighbor.Key.Y < P.GridPos.Y + NY)
					{
						ExistingNeighbor = &P;
						break;
					}
				}

				if (ExistingNeighbor)
				{
					// If neighbor exists, they MUST match doors
					bool bThisHasDoor = (RotatedMask & (int32)Neighbor.Value) != 0;
					bool bNeighborHasDoor = (ExistingNeighbor->ConnectionMask & (int32)OppositeDirection((int32)Neighbor.Value)) != 0;

					if (bThisHasDoor != bNeighborHasDoor)
					{
						return false; // Conflict: Door vs Wall
					}
				}
			}
		}
	}

	if (!bIsStartRoom && !(RotatedMask & RequiredConnectionMask))
	{
		return false;
	}

	FDungeonRoomPlacement NewRoom;
	NewRoom.GridPos       = GridPos;
	NewRoom.RoomDataIndex = RoomIndex;
	NewRoom.ConnectionMask = RotatedMask;
	NewRoom.Rotation      = Rotation;
	NewRoom.WorldOrigin   = bIsStartRoom ? DungeonStartTransform.GetLocation() : GridToWorld(GridPos, RoomIndex);

	for (int32 X = 0; X < SizeX; ++X)
	{
		for (int32 Y = 0; Y < SizeY; ++Y)
		{
			OccupiedCells.Add(GridPos + FIntPoint(X, Y));
		}
	}

	OutPlacements.Add(NewRoom);
	return true;
}


FVector FDungeonGenerationTask::GridToWorld(FIntPoint GridPos, int32 RoomIndex) const
{
	// Calculate local offset in grid space using UNIFORM global tile size
	FVector LocalOffset(
		GridPos.X * GlobalTileSize.X,
		GridPos.Y * GlobalTileSize.Y,
		0.f
	);

	// Transform local offset by the dungeon's base transform
	return DungeonStartTransform.TransformPosition(LocalOffset);
}

int32 FDungeonGenerationTask::RotateMask(int32 Mask, int32 Steps)
{
	Steps = (Steps % 4 + 4) % 4;
	if (Steps == 0) return Mask;

	int32 NewMask = 0;
	auto RotBit = [](int32 m, EDungeonDirection From, EDungeonDirection To) {
		return (m & (int32)From) ? (int32)To : 0;
	};

	for (int32 i = 0; i < Steps; ++i)
	{
		int32 North = RotBit(Mask, EDungeonDirection::North, EDungeonDirection::East);
		int32 East  = RotBit(Mask, EDungeonDirection::East, EDungeonDirection::South);
		int32 South = RotBit(Mask, EDungeonDirection::South, EDungeonDirection::West);
		int32 West  = RotBit(Mask, EDungeonDirection::West, EDungeonDirection::North);
		Mask = North | East | South | West;
	}
	return Mask;
}

int32 FDungeonGenerationTask::OppositeDirection(int32 DirMask)
{
	int32 Result = 0;
	if (DirMask & (int32)EDungeonDirection::North) Result |= (int32)EDungeonDirection::South;
	if (DirMask & (int32)EDungeonDirection::South) Result |= (int32)EDungeonDirection::North;
	if (DirMask & (int32)EDungeonDirection::East)  Result |= (int32)EDungeonDirection::West;
	if (DirMask & (int32)EDungeonDirection::West)  Result |= (int32)EDungeonDirection::East;
	return Result;
}
