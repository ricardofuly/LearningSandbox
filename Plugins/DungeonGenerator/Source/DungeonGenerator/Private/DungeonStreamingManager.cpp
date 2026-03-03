// Fill out your copyright notice in the Description page of Project Settings.


#include "DungeonStreamingManager.h"

#include "DungeonGeneratorSubsystem.h"
#include "Actors/DungeonRoomActor.h"
#include "Data/DungeonGeneratorConfig.h"
#include "Data/DungeonRoomData.h"
#include "Engine/LevelStreamingDynamic.h"
#include "Types/DungeonTypes.h"


class UDungeonRoomData;
// Sets default values
ADungeonStreamingManager::ADungeonStreamingManager()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

void ADungeonStreamingManager::SetOwnerSubsystem(UDungeonGeneratorSubsystem* InSubsystem)
{
	OwnerSubsystem = InSubsystem;
}

void ADungeonStreamingManager::LoadDungeonLayout(const FDungeonLayout& Layout, UDungeonGeneratorConfig* Config)
{
    if (!Config || Layout.Rooms.IsEmpty()) 
    {
        if (OwnerSubsystem.IsValid()) OwnerSubsystem->NotifyAllRoomsLoaded(false);
        return;
    }
    // ---- Pre-resolve todos os RoomData pelo mesmo índice usado na geração ----
    // Índice 0 = Start, 1 = End, 2+ = Pool (igual ao snapshot da Task)
    TArray<UDungeonRoomData*> ResolvedRooms;
    ResolvedRooms.Add(Config->StartRoom.LoadSynchronous());   // [0]
    ResolvedRooms.Add(Config->EndRoom.LoadSynchronous());     // [1]
    for (auto& RoomPtr : Config->RoomPool)
        ResolvedRooms.Add(RoomPtr.LoadSynchronous());         // [2], [3], [4]...
    // Debug
    UE_LOG(LogTemp, Warning, TEXT("ResolvedRooms: %d"), ResolvedRooms.Num());
    for (int32 k = 0; k < ResolvedRooms.Num(); ++k)
        UE_LOG(LogTemp, Warning, TEXT("  [%d] = %s"), k, ResolvedRooms[k] ? *ResolvedRooms[k]->GetName() : TEXT("NULL"));
    CachedConfig   = Config;
    RoomPlacements = Layout.Rooms;
    PendingLoads   = 0;
    LoadedCount    = 0;
    UWorld* World = GetWorld();
    for (int32 i = 0; i < Layout.Rooms.Num(); ++i)
    {
        const FDungeonRoomPlacement& Room = Layout.Rooms[i];
        if (!ResolvedRooms.IsValidIndex(Room.RoomDataIndex))
        {
            UE_LOG(LogTemp, Warning, TEXT("Room %d: índice %d fora do range!"), i, Room.RoomDataIndex);
            continue;
        }
        UDungeonRoomData* RoomData = ResolvedRooms[Room.RoomDataIndex];
        if (!RoomData || RoomData->RoomLevel.IsNull())
        {
            UE_LOG(LogTemp, Warning, TEXT("Room %d: RoomData=%s, RoomLevel=%s"),
                i,
                RoomData ? *RoomData->GetName() : TEXT("NULL"),
                RoomData ? *RoomData->RoomLevel.ToString() : TEXT("N/A"));
            continue;
        }
        bool bSuccess = false;
        FString LevelName = FString::Printf(TEXT("DungeonRoom_%d_%d"), UniqueNameIdx++, i);

        FRotator TotalRotation = BaseTransform.Rotator();
        TotalRotation.Yaw += Room.Rotation;

        ULevelStreamingDynamic* StreamingLevel =
            ULevelStreamingDynamic::LoadLevelInstanceBySoftObjectPtr(
                World, RoomData->RoomLevel,
                Room.WorldOrigin,
                TotalRotation,
                bSuccess, LevelName);
        
        UE_LOG(LogTemp, Warning, TEXT("Room %d: bSuccess=%d, StreamingLevel=%s, Origin=(%.0f,%.0f,%.0f)"),
        i, bSuccess,
        StreamingLevel ? TEXT("OK") : TEXT("NULL"),
        Room.WorldOrigin.X, Room.WorldOrigin.Y, Room.WorldOrigin.Z);
        
        if (bSuccess && StreamingLevel)
        {
            StreamedLevels.Add(StreamingLevel);
            StreamingLevel->OnLevelLoaded.AddDynamic(this, &ADungeonStreamingManager::OnRoomLevelLoaded);
            PendingLoads++;
        }
        else
        {
            UE_LOG(LogTemp, Warning, TEXT("Room %d: LoadLevelInstanceBySoftObjectPtr falhou!"), i);
        }
    }
    if (PendingLoads <= 0 && OwnerSubsystem.IsValid())
        OwnerSubsystem->NotifyAllRoomsLoaded(false);
}

void ADungeonStreamingManager::UnloadAll()
{
    UWorld* World = GetWorld();
    for (ULevelStreamingDynamic* Level : StreamedLevels)
    {
        if (Level)
        {
            Level->SetIsRequestingUnloadAndRemoval(true);
        }
    }
    StreamedLevels.Empty();
    RoomPlacements.Empty();
    PendingLoads = 0;
    LoadedCount  = 0;
}

void ADungeonStreamingManager::OnRoomLevelLoaded()
{
    UE_LOG(LogTemp, Warning, TEXT("OnRoomLevelLoaded! LoadedCount=%d / PendingLoads=%d"), LoadedCount+1, PendingLoads);
    
    LoadedCount++;
    // Find the streaming level that just loaded and its room actor
    // We search for the most-recently-loaded level whose index corresponds to LoadedCount-1
    const int32 RoomIndex = LoadedCount - 1;
    ADungeonRoomActor* RoomActor = nullptr;
    if (StreamedLevels.IsValidIndex(RoomIndex))
    {
        ULevelStreamingDynamic* StreamedLevel = StreamedLevels[RoomIndex];
        if (StreamedLevel && StreamedLevel->GetLoadedLevel())
        {
            for (AActor* Actor : StreamedLevel->GetLoadedLevel()->Actors)
            {
                RoomActor = Cast<ADungeonRoomActor>(Actor);
                if (RoomActor) break;
            }
        }
    }
    if (OwnerSubsystem.IsValid())
        OwnerSubsystem->NotifyRoomLoaded(RoomIndex, RoomActor);
    if (LoadedCount >= PendingLoads && OwnerSubsystem.IsValid())
        OwnerSubsystem->NotifyAllRoomsLoaded(true);
}


