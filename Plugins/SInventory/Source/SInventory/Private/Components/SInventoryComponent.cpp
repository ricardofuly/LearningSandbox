// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/SInventoryComponent.h"

#include "Data/SItemData.h"
#include "Net/UnrealNetwork.h"



struct FEquippedItem;

// Sets default values for this component's properties
USInventoryComponent::USInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	
	SetIsReplicatedByDefault(true);	
}

void USInventoryComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	DOREPLIFETIME(ThisClass, Items);
}

bool USInventoryComponent::AddItem(USItemData* ItemData, int32 Quantity)
{
	if (!ItemData || Quantity <= 0 || !GetOwner()->HasAuthority())
	{
		return false;
	}
	
	FItemInstance* ExistingItem = Items.ItemInstances.FindByPredicate([ItemData](const FItemInstance& Item){ return Item.ItemData == ItemData; });

	if (ExistingItem)
	{
		if (ExistingItem->Quantity < ItemData->MaxStack)
		{
			ExistingItem->Quantity += Quantity;
			Items.MarkItemDirty(*ExistingItem);
			HandleItemAdded(*ExistingItem);
		}
	}
	else
	{
		FItemInstance& NewItem = Items.ItemInstances.AddDefaulted_GetRef();
		NewItem.ItemData = ItemData;
		NewItem.Quantity = Quantity;
		NewItem.InstanceID = FGuid::NewGuid();
		
		Items.MarkItemDirty(NewItem);
		HandleItemAdded(NewItem);
	}	
	
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Green, FString::Printf(TEXT("Item Added: %s"), ItemData ? *ItemData->GetName() : TEXT("Invalid")));
	}

	return true;
}

bool USInventoryComponent::RemoveItemByInstanceID(const FGuid& InstanceID, int32 Quantity)
{
	if (!GetOwner()->HasAuthority())
	{
		return false;
	}

	for (int32 i = 0; i < Items.ItemInstances.Num(); i++)
	{
		FItemInstance& Item = Items.ItemInstances[i];

		if (Item.InstanceID == InstanceID)
		{
			Item.Quantity -= Quantity;

			if (Item.Quantity <= 0)
			{
				Items.ItemInstances.RemoveAt(i);
				Items.MarkArrayDirty();
				
				if (GEngine)
				{
					GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Yellow, FString::Printf(TEXT("Item Changed: %s | Quantity: %d"), Item.ItemData ? *Item.ItemData->GetName() : TEXT("Invalid"), Quantity));
				}
			}
			else
			{
				Items.MarkItemDirty(Item);
			}

			return true;
		}
	}

	return false;
}

FItemInstance* USInventoryComponent::FindItem(const FGuid& InstanceID)
{
	for (FItemInstance& Item : Items.ItemInstances)
	{
		if (Item.InstanceID == InstanceID)
		{
			return &Item;
		}
	}

	return nullptr;
}


// Called when the game starts
void USInventoryComponent::BeginPlay()
{
	Super::BeginPlay();
	
	Items.OwnerComponent = this;
}

void USInventoryComponent::HandleItemAdded(const FItemInstance& Item)
{
	OnItemAdded.Broadcast(Item);
}


