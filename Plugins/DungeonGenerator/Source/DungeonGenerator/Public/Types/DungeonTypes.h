#pragma once

#include "CoreMinimal.h"
#include "DungeonTypes.generated.h"

UENUM(BlueprintType, meta = (Bitflags, UseEnumValuesAsMaskValuesInEditor = "true"))
enum class EDungeonDirection : uint8
{
	None  = 0      UMETA(Hidden),
	North = 1 << 0 UMETA(DisplayName = "North"),
	South = 1 << 1 UMETA(DisplayName = "South"),
	East  = 1 << 2 UMETA(DisplayName = "East"),
	West  = 1 << 3 UMETA(DisplayName = "West"),
};
ENUM_CLASS_FLAGS(EDungeonDirection);


/** Placement data for a single room produced by the generation algorithm.
 *  Pure data — no UObject references — safe to build on a background thread. */
USTRUCT(BlueprintType)
struct DUNGEONGENERATOR_API FDungeonRoomPlacement
{
	GENERATED_BODY()
	/** Position on the integer dungeon grid */
	UPROPERTY(BlueprintReadOnly, Category = "Dungeon")
	FIntPoint GridPos = FIntPoint::ZeroValue;
	/** World-space origin where this room's sub-level should be loaded */
	UPROPERTY(BlueprintReadOnly, Category = "Dungeon")
	FVector WorldOrigin = FVector::ZeroVector;
	/** Index into UDungeonGeneratorConfig::RoomPool */
	UPROPERTY(BlueprintReadOnly, Category = "Dungeon")
	int32 RoomDataIndex = 0;
	/** Which sides have open connectors (bitmask of EDungeonDirection) */
	UPROPERTY(BlueprintReadOnly, Category = "Dungeon")
	int32 ConnectionMask = 0;
	/** Rotation offset (in degrees) to apply to this room instance */
	UPROPERTY(BlueprintReadOnly, Category = "Dungeon")
	float Rotation = 0.f;
};


/** Result returned from the background generation task to the game thread. */
struct DUNGEONGENERATOR_API FDungeonLayout
{
	TArray<FDungeonRoomPlacement> Rooms;
	bool bSuccess = false;
	FString ErrorMessage;
};