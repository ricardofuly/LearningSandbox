// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/SGameplayAbility.h"
#include "AbilitySystem/Effects/SGameplayEffect.h"
#include "Engine/DataAsset.h"
#include "SPlayerInitialData.generated.h"

USTRUCT(BlueprintType)
struct FSPlayerAbilitySet
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (Categories = "InputTag"))
	FGameplayTag InputTag;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<USGameplayAbility> AbilityToGrant;

	bool IsValid() const;
};

UCLASS()
class SANDBOX_API USPlayerInitialData : public UDataAsset
{
	GENERATED_BODY()
public:
	
	virtual void GiveToAbilitySystemComponent(USAbilitySystemComponent* InASCToGive, int32 ApplyLevel = 1) const;
	void GrantAbilities(const TArray<TSubclassOf<USGameplayAbility>>& InAbilities, USAbilitySystemComponent* InASCToGive, int32 ApplyLevel) const;
	
	UPROPERTY(EditDefaultsOnly, Category="StartUpData", meta = (TitleProperty = "InputTag"))
	TArray<FSPlayerAbilitySet> HeroStartUpAbilitySet;
	
	UPROPERTY(EditDefaultsOnly, Category="StartUpData")
	TArray<TSubclassOf<USGameplayAbility>> ActiveOnGivenAbilities;

	UPROPERTY(EditDefaultsOnly, Category="StartUpData")
	TArray<TSubclassOf<USGameplayAbility>> ReactiveAbilities;

	UPROPERTY(EditDefaultsOnly, Category="StartUpData")
	TArray<TSubclassOf<UGameplayEffect>> StartUpGameplayEffects;
};
