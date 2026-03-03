// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/DungeonRoomActor.h"


ADungeonRoomActor::ADungeonRoomActor()
{
	PrimaryActorTick.bCanEverTick = false;
	
	RoomRoot = CreateDefaultSubobject<USceneComponent>(TEXT("RoomRoot"));
	SetRootComponent(RoomRoot);
}

void ADungeonRoomActor::OnRoomInitialized_Implementation(const UDungeonRoomData* RoomData, int32 RoomIndex)
{
	// Base implementation is intentionally empty.
	// Override in Blueprint to spawn enemies, loot, set lighting, etc.
	UE_LOG(LogTemp, Log, TEXT("Room %d initialized."), RoomIndex);
}
