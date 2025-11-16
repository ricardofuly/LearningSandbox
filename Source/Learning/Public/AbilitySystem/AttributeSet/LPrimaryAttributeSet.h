// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AttributeSet.h"
#include "LBaseAttributeSet.h"
#include "LPrimaryAttributeSet.generated.h"

/**
 * 
 */
UCLASS()
class LEARNING_API ULPrimaryAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
public:
	ULPrimaryAttributeSet();
	
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	virtual void PreAttributeBaseChange(const FGameplayAttribute& Attribute, float& NewValue) const override;
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;
	
	// Attributes
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Strength)
	FGameplayAttributeData Strength;
	ATTRIBUTE_ACCESSORS(ULPrimaryAttributeSet, Strength);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Magic)
	FGameplayAttributeData Magic;
	ATTRIBUTE_ACCESSORS(ULPrimaryAttributeSet, Magic);
	
protected:
	
	UFUNCTION()
	void OnRep_Strength(const FGameplayAttributeData& OldValue) const {GAMEPLAYATTRIBUTE_REPNOTIFY(ULPrimaryAttributeSet, Strength, OldValue);}

	UFUNCTION()
	void OnRep_Magic(const FGameplayAttributeData& OldValue) const {GAMEPLAYATTRIBUTE_REPNOTIFY(ULPrimaryAttributeSet, Magic, OldValue);}	
	
};
