// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/SGameplayAbility.h"
#include "AbilitySystem/Effects/SGameplayEffect.h"
#include "Engine/DataAsset.h"
#include "SPlayerInitialData.generated.h"

/**
 * 
 */
UCLASS()
class SANDBOX_API USPlayerInitialData : public UDataAsset
{
	GENERATED_BODY()
public:
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<TObjectPtr<USGameplayAbility>> InitialAbilities;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<TSubclassOf<USGameplayEffect>> InitialEffects;
};
