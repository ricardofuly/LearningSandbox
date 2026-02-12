#include "Types/SInventoryTypes.h"

#include "Components/SInventoryComponent.h"
#include "Data/SItemData.h"

// #include "Components/SInventoryComponent.h"
// #include "Data/SItemData.h"

void FItemInstance::PreReplicatedRemove(const struct FItemFastArray& InArraySerializer)
{
	// Remove from UI
	if (InArraySerializer.OwnerComponent)
	{
		InArraySerializer.OwnerComponent->OnItemChanged.Broadcast(*this);
	}
}

void FItemInstance::PostReplicatedAdd(const struct FItemFastArray& InArraySerializer)
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Green, FString::Printf(TEXT("Item Added: %s"), ItemData ? *ItemData->GetName() : TEXT("Invalid")));
	}

	/* 
	 *   - Update UI,
	 *   - Play Sound,
	 *	 - Notify Inventory Component 
	 */
	
	if (InArraySerializer.OwnerComponent)
	{
		InArraySerializer.OwnerComponent->OnItemAdded.Broadcast(*this);
		InArraySerializer.OwnerComponent->HandleItemAdded(*this);
	}
}

void FItemInstance::PostReplicatedChange(const struct FItemFastArray& InArraySerializer)
{
	// Update UI
	if (InArraySerializer.OwnerComponent)
	{
		InArraySerializer.OwnerComponent->OnItemRemoved.Broadcast(*this);
	}
}
