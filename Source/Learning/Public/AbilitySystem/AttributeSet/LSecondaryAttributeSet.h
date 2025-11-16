// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AttributeSet.h"
#include "LBaseAttributeSet.h"
#include "LSecondaryAttributeSet.generated.h"

/**
 * 
 */
UCLASS()
class LEARNING_API ULSecondaryAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
public:
	ULSecondaryAttributeSet();
	
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	virtual void PreAttributeBaseChange(const FGameplayAttribute& Attribute, float& NewValue) const override;
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;
	
	void AddXP(float Amount, const FGameplayEffectModCallbackData& Data);
	float GetRequiredXPForNextLevel() const;
	
	// Attributes
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Defense)
	FGameplayAttributeData Defense;
	ATTRIBUTE_ACCESSORS(ULSecondaryAttributeSet, Defense);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MagicDefense)
	FGameplayAttributeData MagicDefense;
	ATTRIBUTE_ACCESSORS(ULSecondaryAttributeSet, MagicDefense);
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_SlashStrength)
	FGameplayAttributeData SlashStrength;
	ATTRIBUTE_ACCESSORS(ULSecondaryAttributeSet, SlashStrength);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_SlashResistance)
	FGameplayAttributeData SlashResistance;
	ATTRIBUTE_ACCESSORS(ULSecondaryAttributeSet, SlashResistance);
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_StrikeStrength)
	FGameplayAttributeData StrikeStrength;
	ATTRIBUTE_ACCESSORS(ULSecondaryAttributeSet, StrikeStrength);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_StrikeResistance)
	FGameplayAttributeData StrikeResistance;
	ATTRIBUTE_ACCESSORS(ULSecondaryAttributeSet, StrikeResistance);
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_KnockdownPower)
	FGameplayAttributeData KnockdownPower;
	ATTRIBUTE_ACCESSORS(ULSecondaryAttributeSet, KnockdownPower);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_KnockdownResistance)
	FGameplayAttributeData KnockdownResistance;
	ATTRIBUTE_ACCESSORS(ULSecondaryAttributeSet, KnockdownResistance);
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_XP)
	FGameplayAttributeData XP;
	ATTRIBUTE_ACCESSORS(ULSecondaryAttributeSet, XP);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Level)
	FGameplayAttributeData Level;
	ATTRIBUTE_ACCESSORS(ULSecondaryAttributeSet, Level);
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Gold)
	FGameplayAttributeData Gold;
	ATTRIBUTE_ACCESSORS(ULSecondaryAttributeSet, Gold);
	
protected:
	
	UFUNCTION()
	void OnRep_Defense(const FGameplayAttributeData& OldValue) const {GAMEPLAYATTRIBUTE_REPNOTIFY(ULSecondaryAttributeSet, Defense, OldValue);}

	UFUNCTION()
	void OnRep_MagicDefense(const FGameplayAttributeData& OldValue) const {GAMEPLAYATTRIBUTE_REPNOTIFY(ULSecondaryAttributeSet, MagicDefense, OldValue);}

	UFUNCTION()
	void OnRep_SlashStrength(const FGameplayAttributeData& OldValue) const {GAMEPLAYATTRIBUTE_REPNOTIFY(ULSecondaryAttributeSet, SlashStrength, OldValue);}

	UFUNCTION()
	void OnRep_SlashResistance(const FGameplayAttributeData& OldValue) const {GAMEPLAYATTRIBUTE_REPNOTIFY(ULSecondaryAttributeSet, SlashResistance, OldValue);}

	UFUNCTION()
	void OnRep_StrikeStrength(const FGameplayAttributeData& OldValue) const {GAMEPLAYATTRIBUTE_REPNOTIFY(ULSecondaryAttributeSet, StrikeStrength, OldValue);}

	UFUNCTION()
	void OnRep_StrikeResistance(const FGameplayAttributeData& OldValue) const {GAMEPLAYATTRIBUTE_REPNOTIFY(ULSecondaryAttributeSet, StrikeResistance, OldValue);}

	UFUNCTION()
	void OnRep_KnockdownPower(const FGameplayAttributeData& OldValue) const {GAMEPLAYATTRIBUTE_REPNOTIFY(ULSecondaryAttributeSet, KnockdownPower, OldValue);}

	UFUNCTION()
	void OnRep_KnockdownResistance(const FGameplayAttributeData& OldValue) const {GAMEPLAYATTRIBUTE_REPNOTIFY(ULSecondaryAttributeSet, KnockdownResistance, OldValue);}

	UFUNCTION()
	void OnRep_XP(const FGameplayAttributeData& OldValue) const {GAMEPLAYATTRIBUTE_REPNOTIFY(ULSecondaryAttributeSet, XP, OldValue);}

	UFUNCTION()
	void OnRep_Level(const FGameplayAttributeData& OldValue) const {GAMEPLAYATTRIBUTE_REPNOTIFY(ULSecondaryAttributeSet, Level, OldValue);}

	UFUNCTION()
	void OnRep_Gold(const FGameplayAttributeData& OldValue) const {GAMEPLAYATTRIBUTE_REPNOTIFY(ULSecondaryAttributeSet, Gold, OldValue);}
};
