// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "SAttributeSetBase.h"
#include "SStackAttributeSet.generated.h"

/**
 * 
 */
UCLASS()
class SANDBOX_API USStackAttributeSet : public USAttributeSetBase
{
	GENERATED_BODY()
public:
	
	USStackAttributeSet();
	
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	virtual void PreAttributeBaseChange(const FGameplayAttribute& Attribute, float& NewValue) const override;
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;
	
	// Attributes
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_DashStacks)
	FGameplayAttributeData DashStacks;
	ATTRIBUTE_ACCESSORS(ThisClass, DashStacks);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_DashMaxStacks)
	FGameplayAttributeData DashMaxStacks;
	ATTRIBUTE_ACCESSORS(ThisClass, DashMaxStacks);
	
protected:
	
	UFUNCTION()
	FORCEINLINE void OnRep_DashStacks(const FGameplayAttributeData& OldValue) const {GAMEPLAYATTRIBUTE_REPNOTIFY(ThisClass, DashStacks, OldValue);}

	UFUNCTION()
	FORCEINLINE void OnRep_DashMaxStacks(const FGameplayAttributeData& OldValue) const {GAMEPLAYATTRIBUTE_REPNOTIFY(ThisClass, DashMaxStacks, OldValue);}
};
