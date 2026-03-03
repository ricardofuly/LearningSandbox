// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DungeonRoomActor.generated.h"

class UDungeonRoomData;

UCLASS()
class DUNGEONGENERATOR_API ADungeonRoomActor : public AActor
{
	GENERATED_BODY()

public:
	ADungeonRoomActor();
	
	/**
	 * Called by the streaming manager once this room's level is fully loaded.
	 * @param RoomData  The data asset that configured this room.
	 * @param RoomIndex Position index in the dungeon layout array.
	 */
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Dungeon|Room")
	void OnRoomInitialized(const UDungeonRoomData* RoomData, int32 RoomIndex);
	
	virtual void OnRoomInitialized_Implementation(const UDungeonRoomData* RoomData, int32 RoomIndex);
	/**
	 * Scene components placed as children of this actor in the sub-level
	 * to mark doorway positions. Tag them "DoorConnector" for easy query.
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Dungeon|Room")
	TObjectPtr<USceneComponent> RoomRoot;
};
