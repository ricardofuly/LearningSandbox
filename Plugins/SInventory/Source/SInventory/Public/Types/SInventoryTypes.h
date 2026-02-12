#pragma once

#include "CoreMinimal.h"
#include "Net/Serialization/FastArraySerializer.h"
#include "SInventoryTypes.generated.h"


class USInventoryComponent;
class USItemData;

// Enums
UENUM(BlueprintType)
enum class EItemType : uint8
{
	EIT_None		= 0		UMETA(DisplayName = "None"),
	EIT_Armour		= 1		UMETA(DisplayName = "Armour"),
	EIT_Weapon		= 2		UMETA(DisplayName = "Weapon"),
	EIT_Consumable	= 3		UMETA(DisplayName = "Consumable"),
	EIT_Misc		= 4		UMETA(DisplayName = "Misc"),
	EIT_Quest		= 5		UMETA(DisplayName = "Quest")	
};

UENUM(BlueprintType)
enum class EEquipmentSlot : uint8
{
	EES_None	= 0		UMETA(DisplayName = "None"),
	EES_Head	= 1		UMETA(DisplayName = "Head"),
	EES_Chest	= 2		UMETA(DisplayName = "Chest"),
	EES_Legs	= 3		UMETA(DisplayName = "Legs"),
	EES_Weapon	= 4		UMETA(DisplayName = "Weapon"),
	EES_OffHand = 5		UMETA(DisplayName = "OffHand")	
};


//


struct FItemFastArray;

// Structs

USTRUCT(BlueprintType)
struct FItemInstance : public FFastArraySerializerItem
{
	GENERATED_BODY()
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	USItemData* ItemData = nullptr;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Quantity = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGuid InstanceID;
	
	// Overriding PreReplicatedRemove and PostReplicatedAdd (optional)
	void PreReplicatedRemove(const struct FItemFastArray& InArraySerializer);
	void PostReplicatedAdd(const struct FItemFastArray& InArraySerializer);
	void PostReplicatedChange(const struct FItemFastArray& InArraySerializer);
};

USTRUCT(BlueprintType)
struct FItemFastArray : public FFastArraySerializer
{
	GENERATED_BODY()
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<FItemInstance> ItemInstances;
	
	UPROPERTY(NotReplicated)
	USInventoryComponent* OwnerComponent = nullptr;
	
	// Custom NetDeltaSerialize implementation
	bool NetDeltaSerialize(FNetDeltaSerializeInfo& DeltaParms)
	{
		return FFastArraySerializer::FastArrayDeltaSerialize<FItemInstance, FItemFastArray>(ItemInstances, DeltaParms, *this);
	}
};

template<>
struct TStructOpsTypeTraits<FItemFastArray> : public TStructOpsTypeTraitsBase2<FItemFastArray>
{
	enum
	{
		WithNetDeltaSerializer = true,
	};
};