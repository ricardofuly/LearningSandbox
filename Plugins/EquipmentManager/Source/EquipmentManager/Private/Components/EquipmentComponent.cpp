// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/EquipmentComponent.h"

#include "Components/SInventoryComponent.h"
#include "Data/SItemData.h"
#include "Net/UnrealNetwork.h"


// Sets default values for this component's properties
UEquipmentComponent::UEquipmentComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	
	SetIsReplicatedByDefault(true);
	
}

void UEquipmentComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	DOREPLIFETIME(ThisClass, Equipment);
}

bool UEquipmentComponent::EquipItem(const FItemInstance& Item)
{
	if (!GetOwner()->HasAuthority())
	{
		return false;
	}
	
	if (!Item.ItemData)
	{
		return false;
	}

	const EEquipmentSlot Slot = Item.ItemData->EquipSlot;
	
	UnequipItem(Slot);

	FEquippedItem& NewEquip = Equipment.Items.AddDefaulted_GetRef();
	NewEquip.Slot = Slot;
	NewEquip.Item = Item;

	USkeletalMeshComponent* SkeletalMesh = NewEquip.Item.ItemData->ItemSkeletalMesh;
	UStaticMeshComponent* StaticMesh = NewEquip.Item.ItemData->ItemStaticMesh;
	if (IsValid(SkeletalMesh))
	{
		SkeletalMesh->AttachToComponent(GetOwner()->GetRootComponent(), FAttachmentTransformRules::SnapToTargetIncludingScale, NewEquip.Item.ItemData->SocketToAttach);
	}

	if (IsValid(StaticMesh))
	{
		StaticMesh->AttachToComponent(GetOwner()->GetRootComponent(), FAttachmentTransformRules::SnapToTargetIncludingScale, NewEquip.Item.ItemData->SocketToAttach);
	}
	
	
	if (USInventoryComponent* INV = Cast<USInventoryComponent>(GetOwner()->GetComponentByClass(USInventoryComponent::StaticClass())))
	{
		if (INV->FindItem(Item.InstanceID))
		{
			INV->RemoveItemByInstanceID(Item.InstanceID, 1);
		}
	}

	Equipment.MarkItemDirty(NewEquip);
	return true;
}

bool UEquipmentComponent::UnequipItem(EEquipmentSlot Slot)
{
	if (!GetOwner()->HasAuthority())
	{
		return false;
	}

	for (int32 i = 0; i < Equipment.Items.Num(); i++)
	{
		if (Equipment.Items[i].Slot == Slot)
		{
			Equipment.Items.RemoveAt(i);

			if (IsValid(Equipment.Items[i].Item.ItemData->ItemSkeletalMesh))
			{
				Equipment.Items[i].Item.ItemData->ItemSkeletalMesh->DestroyComponent();
			}

			if (IsValid(Equipment.Items[i].Item.ItemData->ItemStaticMesh))
			{
				Equipment.Items[i].Item.ItemData->ItemStaticMesh->DestroyComponent();
			}
			
			if (USInventoryComponent* INV = Cast<USInventoryComponent>(GetOwner()->GetComponentByClass(USInventoryComponent::StaticClass())))
			{
				if (INV->FindItem(Equipment.Items[i].Item.InstanceID))
				{
					INV->AddItem(Equipment.Items[i].Item.ItemData, 1);
				}
			}
			
			Equipment.MarkArrayDirty();
			return true;
		}
	}

	return false;
}


FEquippedItem* UEquipmentComponent::FindItemBySlot(EEquipmentSlot Slot)
{
	for (FEquippedItem& Item : Equipment.Items)
	{
		if (Item.Slot == Slot)
		{
			return &Item;
		}
	}

	return nullptr;
}

// Called when the game starts
void UEquipmentComponent::BeginPlay()
{
	Super::BeginPlay();
	
	Equipment.OwnerComponent = this;
}


