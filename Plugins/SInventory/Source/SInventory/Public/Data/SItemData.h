// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Types/SInventoryTypes.h"
#include "SItemData.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class SINVENTORY_API USItemData : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FName ItemID;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FText Name;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	EItemType ItemType;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	EEquipmentSlot EquipSlot;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	bool UseSkeletalMesh = false;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(EditCondition="UseSkeletalMesh", EditConditionHides))
	USkeletalMeshComponent* ItemSkeletalMesh = nullptr;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(EditCondition="!UseSkeletalMesh", EditConditionHides))
	UStaticMeshComponent* ItemStaticMesh = nullptr;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FName SocketToAttach = NAME_None;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UTexture2D* Icon;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int32 MaxStack = 1;
};
