// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "SAttributeSetBase.h"
#include "SSecondaryAttributeSet.generated.h"

/**
 * 
 */
UCLASS()
class SANDBOX_API USSecondaryAttributeSet : public USAttributeSetBase
{
	GENERATED_BODY()
public:
	USSecondaryAttributeSet();
	
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	virtual void PreAttributeBaseChange(const FGameplayAttribute& Attribute, float& NewValue) const override;
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;
	
	// Secondary Attributes
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Defense)
	FGameplayAttributeData Defense;
	ATTRIBUTE_ACCESSORS(USSecondaryAttributeSet, Defense);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Endurance)
	FGameplayAttributeData Endurance;
	ATTRIBUTE_ACCESSORS(USSecondaryAttributeSet, Endurance);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_FireResistance)
	FGameplayAttributeData FireResistance;
	ATTRIBUTE_ACCESSORS(USSecondaryAttributeSet, FireResistance);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_IceResistance)
	FGameplayAttributeData IceResistance;
	ATTRIBUTE_ACCESSORS(USSecondaryAttributeSet, IceResistance);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_ChaosResistance)
	FGameplayAttributeData ChaosResistance;
	ATTRIBUTE_ACCESSORS(USSecondaryAttributeSet, ChaosResistance);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_AllElementalResistance)
	FGameplayAttributeData AllElementalResistance;
	ATTRIBUTE_ACCESSORS(USSecondaryAttributeSet, AllElementalResistance);
	
	
	
protected:
	
	UFUNCTION()
	void OnRep_Defense(const FGameplayAttributeData& OldValue) const {GAMEPLAYATTRIBUTE_REPNOTIFY(USSecondaryAttributeSet, Defense, OldValue);}

	UFUNCTION()
	void OnRep_Endurance(const FGameplayAttributeData& OldValue) const {GAMEPLAYATTRIBUTE_REPNOTIFY(USSecondaryAttributeSet, Endurance, OldValue);}

	UFUNCTION()
	void OnRep_FireResistance(const FGameplayAttributeData& OldValue) const {GAMEPLAYATTRIBUTE_REPNOTIFY(USSecondaryAttributeSet, FireResistance, OldValue);}

	UFUNCTION()
	void OnRep_IceResistance(const FGameplayAttributeData& OldValue) const {GAMEPLAYATTRIBUTE_REPNOTIFY(USSecondaryAttributeSet, IceResistance, OldValue);}

	UFUNCTION()
	void OnRep_ChaosResistance(const FGameplayAttributeData& OldValue) const {GAMEPLAYATTRIBUTE_REPNOTIFY(USSecondaryAttributeSet, ChaosResistance, OldValue);}

	UFUNCTION()
	void OnRep_AllElementalResistance(const FGameplayAttributeData& OldValue) const {GAMEPLAYATTRIBUTE_REPNOTIFY(USSecondaryAttributeSet, AllElementalResistance, OldValue);}
};
