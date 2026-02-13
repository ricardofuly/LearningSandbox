// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Types/EquipmentTypes.h"
#include "EquipmentComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnItemEquipped, const FEquippedItem&, Item);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnItemUnequipped, const FEquippedItem&, Item);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnItemChanged, const FEquippedItem&, Item);

UCLASS(ClassGroup=(Gameplay), meta=(BlueprintSpawnableComponent))
class EQUIPMENTMANAGER_API UEquipmentComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UEquipmentComponent();
	
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	
	// Delegates
	UPROPERTY(BlueprintAssignable)
	FOnItemEquipped OnItemEquipped;

	UPROPERTY(BlueprintAssignable)
	FOnItemUnequipped OnItemUnequipped;

	UPROPERTY(BlueprintAssignable)
	FOnItemChanged OnItemChanged;

	// API
	UFUNCTION(BlueprintCallable, Category= "Equipment")
	bool EquipItem(const FItemInstance& Item);

	UFUNCTION(BlueprintCallable, Category= "Equipment")
	bool UnequipItem(EEquipmentSlot Slot);
	
	FEquippedItem* FindItemBySlot(EEquipmentSlot Slot);
	
	UFUNCTION(BlueprintPure, Category= "Equipment")
	void GetAllEquipments(TArray<FEquippedItem>& OutItems) const { OutItems = Equipment.Items;}

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	
	UPROPERTY(Replicated)
	FEquipmentFastArray Equipment;
};
