// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "SAttributeSetBase.h"
#include "SPrimaryAttributeSet.generated.h"

/**
 * 
 */
UCLASS()
class SANDBOX_API USPrimaryAttributeSet : public USAttributeSetBase
{
	GENERATED_BODY()
public:
	USPrimaryAttributeSet();
	
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	virtual void PreAttributeBaseChange(const FGameplayAttribute& Attribute, float& NewValue) const override;
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;
	
	// Attributes
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_AttackPower)
	FGameplayAttributeData AttackPower;
	ATTRIBUTE_ACCESSORS(USPrimaryAttributeSet, AttackPower);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MagicPower)
	FGameplayAttributeData MagicPower;
	ATTRIBUTE_ACCESSORS(USPrimaryAttributeSet, MagicPower);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Strength)
	FGameplayAttributeData Strength;
	ATTRIBUTE_ACCESSORS(USPrimaryAttributeSet, Strength);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Intellect)
	FGameplayAttributeData Intellect;
	ATTRIBUTE_ACCESSORS(USPrimaryAttributeSet, Intellect);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Agility)
	FGameplayAttributeData Agility;
	ATTRIBUTE_ACCESSORS(USPrimaryAttributeSet, Agility);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_AttackSpeed)
	FGameplayAttributeData AttackSpeed;
	ATTRIBUTE_ACCESSORS(USPrimaryAttributeSet, AttackSpeed);
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_CastSpeed)
	FGameplayAttributeData CastSpeed;
	ATTRIBUTE_ACCESSORS(USPrimaryAttributeSet, CastSpeed);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_CriticalDamage)
	FGameplayAttributeData CriticalDamage;
	ATTRIBUTE_ACCESSORS(USPrimaryAttributeSet, CriticalDamage);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_CriticalChance)
	FGameplayAttributeData CriticalChance;
	ATTRIBUTE_ACCESSORS(USPrimaryAttributeSet, CriticalChance);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_FireDamage)
	FGameplayAttributeData FireDamage;
	ATTRIBUTE_ACCESSORS(USPrimaryAttributeSet, FireDamage);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_IceDamage)
	FGameplayAttributeData IceDamage;
	ATTRIBUTE_ACCESSORS(USPrimaryAttributeSet, IceDamage);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_ChaosDamage)
	FGameplayAttributeData ChaosDamage;
	ATTRIBUTE_ACCESSORS(USPrimaryAttributeSet, ChaosDamage);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_AllElementalDamage)
	FGameplayAttributeData AllElementalDamage;
	ATTRIBUTE_ACCESSORS(USPrimaryAttributeSet, AllElementalDamage);
	
protected:
	
	UFUNCTION()
	void OnRep_AttackPower(const FGameplayAttributeData& OldValue) const {GAMEPLAYATTRIBUTE_REPNOTIFY(USPrimaryAttributeSet, AttackPower, OldValue);}

	UFUNCTION()
	void OnRep_MagicPower(const FGameplayAttributeData& OldValue) const {GAMEPLAYATTRIBUTE_REPNOTIFY(USPrimaryAttributeSet, MagicPower, OldValue);}
	
	UFUNCTION()
	void OnRep_Strength(const FGameplayAttributeData& OldValue) const {GAMEPLAYATTRIBUTE_REPNOTIFY(USPrimaryAttributeSet, Strength, OldValue);}

	UFUNCTION()
	void OnRep_Intellect(const FGameplayAttributeData& OldValue) const {GAMEPLAYATTRIBUTE_REPNOTIFY(USPrimaryAttributeSet, Intellect, OldValue);}

	UFUNCTION()
	void OnRep_Agility(const FGameplayAttributeData& OldValue) const {GAMEPLAYATTRIBUTE_REPNOTIFY(USPrimaryAttributeSet, Agility, OldValue);}

	UFUNCTION()
	void OnRep_AttackSpeed(const FGameplayAttributeData& OldValue) const {GAMEPLAYATTRIBUTE_REPNOTIFY(USPrimaryAttributeSet, AttackSpeed, OldValue);}

	UFUNCTION()
	void OnRep_CastSpeed(const FGameplayAttributeData& OldValue) const {GAMEPLAYATTRIBUTE_REPNOTIFY(USPrimaryAttributeSet, CastSpeed, OldValue);}

	UFUNCTION()
	void OnRep_CriticalDamage(const FGameplayAttributeData& OldValue) const {GAMEPLAYATTRIBUTE_REPNOTIFY(USPrimaryAttributeSet, CriticalDamage, OldValue);}

	UFUNCTION()
	void OnRep_CriticalChance(const FGameplayAttributeData& OldValue) const {GAMEPLAYATTRIBUTE_REPNOTIFY(USPrimaryAttributeSet, CriticalChance, OldValue);}

	UFUNCTION()
	void OnRep_FireDamage(const FGameplayAttributeData& OldValue) const {GAMEPLAYATTRIBUTE_REPNOTIFY(USPrimaryAttributeSet, FireDamage, OldValue);}

	UFUNCTION()
	void OnRep_IceDamage(const FGameplayAttributeData& OldValue) const {GAMEPLAYATTRIBUTE_REPNOTIFY(USPrimaryAttributeSet, IceDamage, OldValue);}

	UFUNCTION()
	void OnRep_ChaosDamage(const FGameplayAttributeData& OldValue) const {GAMEPLAYATTRIBUTE_REPNOTIFY(USPrimaryAttributeSet, ChaosDamage, OldValue);}

	UFUNCTION()
	void OnRep_AllElementalDamage(const FGameplayAttributeData& OldValue) const {GAMEPLAYATTRIBUTE_REPNOTIFY(USPrimaryAttributeSet, AllElementalDamage, OldValue);}
};
