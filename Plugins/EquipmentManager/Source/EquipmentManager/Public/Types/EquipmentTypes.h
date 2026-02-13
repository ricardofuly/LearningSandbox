#pragma once

#include "CoreMinimal.h"
#include "Types/SInventoryTypes.h"
#include "EquipmentTypes.generated.h"


// =======================
// FastArray Item
// =======================

class UEquipmentComponent;

USTRUCT(BlueprintType)
struct FEquippedItem : public FFastArraySerializerItem
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	EEquipmentSlot Slot = EEquipmentSlot::EES_None;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FItemInstance Item;

	void PreReplicatedRemove(const struct FEquipmentFastArray& InArray);
	void PostReplicatedAdd(const struct FEquipmentFastArray& InArray);
	void PostReplicatedChange(const struct FEquipmentFastArray& InArray);
};


// =======================
// FastArray Serializer
// =======================

USTRUCT(BlueprintType)
struct FEquipmentFastArray : public FFastArraySerializer
{
	GENERATED_BODY()

	UPROPERTY()
	TArray<FEquippedItem> Items;

	UPROPERTY()
	UEquipmentComponent* OwnerComponent = nullptr;

	bool NetDeltaSerialize(FNetDeltaSerializeInfo& DeltaParms)
	{
		return FFastArraySerializer::FastArrayDeltaSerialize<
			FEquippedItem,
			FEquipmentFastArray
		>(Items, DeltaParms, *this);
	}
};

// =======================
// Traits
// =======================

template<>
struct TStructOpsTypeTraits<FEquipmentFastArray>
	: public TStructOpsTypeTraitsBase2<FEquipmentFastArray>
{
	enum
	{
		WithNetDeltaSerializer = true,
	};
};
