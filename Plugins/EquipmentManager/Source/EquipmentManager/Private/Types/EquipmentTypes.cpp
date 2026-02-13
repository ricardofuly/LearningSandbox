#include "Types/EquipmentTypes.h"

#include "Components/EquipmentComponent.h"

void FEquippedItem::PreReplicatedRemove(const struct FEquipmentFastArray& InArray)
{
	if (InArray.OwnerComponent)
	{
		InArray.OwnerComponent->OnItemUnequipped.Broadcast(*this);
	}
}

void FEquippedItem::PostReplicatedAdd(const struct FEquipmentFastArray& InArray)
{
	if (InArray.OwnerComponent)
	{
		InArray.OwnerComponent->OnItemEquipped.Broadcast(*this);
	}
}

void FEquippedItem::PostReplicatedChange(const struct FEquipmentFastArray& InArray)
{
	if (InArray.OwnerComponent)
	{
		InArray.OwnerComponent->OnItemChanged.Broadcast(*this);
	}
}
