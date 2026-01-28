// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "Engine/DataAsset.h"
#include "SInteractionDefinition.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class SANDBOX_API USInteractionDefinition : public UDataAsset
{
	GENERATED_BODY()
public:
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float MaxDistance = 250.f;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FText InteractionText;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FGameplayTagContainer RequiredTags;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FGameplayTagContainer BlockedTags;
};
