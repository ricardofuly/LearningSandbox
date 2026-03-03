// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "DungeonGeneratorSubsystem.generated.h"

class ADungeonStreamingManager;
class ADungeonRoomActor;
class UDungeonGeneratorConfig;
struct FDungeonLayout;
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDungeonGenerated, bool, bSuccess);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnRoomLoaded, int32, RoomIndex, ADungeonRoomActor*, RoomActor);

UCLASS()
class DUNGEONGENERATOR_API UDungeonGeneratorSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()
	
public:
	//~ USubsystem
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
	// ---- Blueprint API ------------------------------------------------------
	/** Starts async dungeon generation. Bind delegates before calling this. */
	UFUNCTION(BlueprintCallable, Category = "Dungeon")
	void GenerateDungeon(UDungeonGeneratorConfig* Config, const FTransform& StartTransform);

	/** Starts async dungeon using Config->DungeonOrigin. */
	UFUNCTION(BlueprintCallable, Category = "Dungeon", meta=(DisplayName="Generate Dungeon (Default)"))
	void GenerateDungeonDefault(UDungeonGeneratorConfig* Config);
	
	/** Unloads all streamed room levels and destroys the streaming manager. */
	UFUNCTION(BlueprintCallable, Category = "Dungeon")
	void UnloadDungeon();
	UFUNCTION(BlueprintPure, Category = "Dungeon")
	bool IsGenerating() const { return bIsGenerating; }
	// ---- Delegates ----------------------------------------------------------
	/** Fired once when the full dungeon is ready (or failed). */
	UPROPERTY(BlueprintAssignable, Category = "Dungeon")
	FOnDungeonGenerated OnDungeonGenerated;
	/** Fired on the game thread each time one room finishes streaming in. */
	UPROPERTY(BlueprintAssignable, Category = "Dungeon")
	FOnRoomLoaded OnRoomLoaded;
	// ---- Internal (called by ADungeonStreamingManager) ----------------------
	void NotifyRoomLoaded(int32 RoomIndex, ADungeonRoomActor* RoomActor);
	void NotifyAllRoomsLoaded(bool bSuccess);
private:
	void OnGenerationComplete(FDungeonLayout Layout);
	UPROPERTY()
	TObjectPtr<ADungeonStreamingManager> StreamingManager;
	UPROPERTY()
	TObjectPtr<UDungeonGeneratorConfig> ActiveConfig;
	FTransform ActiveStartTransform;
	bool bIsGenerating = false;
};
