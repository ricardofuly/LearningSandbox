// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Types/SInventoryTypes.h"
#include "SInventoryComponent.generated.h"


class UEquipmentComponent;
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnInventoryItemAdded, const FItemInstance&, Item);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnInventoryItemChanged, const FItemInstance&, Item);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnInventoryItemRemoved, const FItemInstance&, Item);

UCLASS(ClassGroup=(Gameplay), meta=(BlueprintSpawnableComponent, DisplayName = "Inventory Component"))
class SINVENTORY_API USInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	USInventoryComponent();
	
	// Network Replication
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	
	// Delegates
	UPROPERTY(BlueprintAssignable)
	FOnInventoryItemAdded OnItemAdded;
	
	UPROPERTY(BlueprintAssignable)
	FOnInventoryItemChanged OnItemChanged;
	
	UPROPERTY(BlueprintAssignable)
	FOnInventoryItemRemoved OnItemRemoved;
	
	// Inventory API
	UFUNCTION(BlueprintCallable)
	bool AddItem(USItemData* ItemData, int32 Quantity);
	
	UFUNCTION(BlueprintCallable)
	bool RemoveItemByInstanceID(const FGuid& InstanceID, int32 Quantity);
	
	UFUNCTION(BlueprintCallable)
	void GetAllItems(FItemFastArray& InItems) const { InItems = Items; }
	
	// Internal Only
	void HandleItemAdded(const FItemInstance& Item);
	
	FItemInstance* FindItem(const FGuid& InstanceID);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	
	UPROPERTY(VisibleAnywhere, Replicated)
	FItemFastArray Items;
};
