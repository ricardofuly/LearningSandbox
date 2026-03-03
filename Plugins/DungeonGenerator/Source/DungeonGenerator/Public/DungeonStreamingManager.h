// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DungeonStreamingManager.generated.h"

struct FDungeonLayout;
struct FDungeonRoomPlacement;
class UDungeonGeneratorConfig;
class UDungeonGeneratorSubsystem;
class ULevelStreamingDynamic;

UCLASS()
class DUNGEONGENERATOR_API ADungeonStreamingManager : public AActor
{
	GENERATED_BODY()

public:
	ADungeonStreamingManager();
	void SetOwnerSubsystem(UDungeonGeneratorSubsystem* InSubsystem);
	void SetBaseTransform(const FTransform& InTransform) { BaseTransform = InTransform; }
	void LoadDungeonLayout(const FDungeonLayout& Layout, UDungeonGeneratorConfig* Config);
	void UnloadAll();
	
private:
	UFUNCTION()
	void OnRoomLevelLoaded();
	UPROPERTY()
	TArray<TObjectPtr<ULevelStreamingDynamic>> StreamedLevels;
	// The transform where the first room (0,0) is placed
	FTransform BaseTransform;

	// Parallel array — same index as StreamedLevels
	TArray<FDungeonRoomPlacement> RoomPlacements;
	TWeakObjectPtr<UDungeonGeneratorSubsystem> OwnerSubsystem;
	TWeakObjectPtr<UDungeonGeneratorConfig> CachedConfig;
	int32 PendingLoads   = 0;
	int32 LoadedCount    = 0;
	int32 UniqueNameIdx  = 0;
};
