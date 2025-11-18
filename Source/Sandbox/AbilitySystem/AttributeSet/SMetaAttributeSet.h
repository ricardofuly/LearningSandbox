// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "SAttributeSetBase.h"
#include "SMetaAttributeSet.generated.h"

/**
 * 
 */
UCLASS()
class SANDBOX_API USMetaAttributeSet : public USAttributeSetBase
{
	GENERATED_BODY()
public:
	USMetaAttributeSet();
	
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	virtual void PreAttributeBaseChange(const FGameplayAttribute& Attribute, float& NewValue) const override;
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;
	
	void AddXP(float Amount, const FGameplayEffectModCallbackData& Data, const FGameplayEventData& Payload);
	float GetRequiredXPForNextLevel() const;
	
	// Attributes
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Health)
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(ThisClass, Health);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxHealth)
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(ThisClass, MaxHealth);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Mana)
	FGameplayAttributeData Mana;
	ATTRIBUTE_ACCESSORS(ThisClass, Mana);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxMana)
	FGameplayAttributeData MaxMana;
	ATTRIBUTE_ACCESSORS(ThisClass, MaxMana);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Stamina)
	FGameplayAttributeData Stamina;
	ATTRIBUTE_ACCESSORS(ThisClass, Stamina);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxStamina)
	FGameplayAttributeData MaxStamina;
	ATTRIBUTE_ACCESSORS(ThisClass, MaxStamina);
	
	// XP
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_XP)
	FGameplayAttributeData XP;
	ATTRIBUTE_ACCESSORS(ThisClass, XP);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxXP, meta = (HideFromModifiers))
	FGameplayAttributeData MaxXP;
	ATTRIBUTE_ACCESSORS(ThisClass, MaxXP);
	
	// Level

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Level, meta = (HideFromModifiers))
	FGameplayAttributeData Level;
	ATTRIBUTE_ACCESSORS(ThisClass, Level);
	
	// Currencies
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Gold)
	FGameplayAttributeData Gold;
	ATTRIBUTE_ACCESSORS(ThisClass, Gold);
	
protected:
	
	UFUNCTION()
	FORCEINLINE void OnRep_Health(const FGameplayAttributeData& OldValue) const {GAMEPLAYATTRIBUTE_REPNOTIFY(ThisClass, Health, OldValue);}

	UFUNCTION()
	FORCEINLINE void OnRep_MaxHealth(const FGameplayAttributeData& OldValue) const {GAMEPLAYATTRIBUTE_REPNOTIFY(ThisClass, MaxHealth, OldValue);}

	UFUNCTION()
	FORCEINLINE void OnRep_Mana(const FGameplayAttributeData& OldValue) const {GAMEPLAYATTRIBUTE_REPNOTIFY(ThisClass, Mana, OldValue);}

	UFUNCTION()
	FORCEINLINE void OnRep_MaxMana(const FGameplayAttributeData& OldValue) const {GAMEPLAYATTRIBUTE_REPNOTIFY(ThisClass, MaxMana, OldValue);}

	UFUNCTION()
	FORCEINLINE void OnRep_Stamina(const FGameplayAttributeData& OldValue) const {GAMEPLAYATTRIBUTE_REPNOTIFY(ThisClass, Stamina, OldValue);}

	UFUNCTION()
	FORCEINLINE void OnRep_MaxStamina(const FGameplayAttributeData& OldValue) const {GAMEPLAYATTRIBUTE_REPNOTIFY(ThisClass, MaxStamina, OldValue);}
	
	UFUNCTION()
	FORCEINLINE void OnRep_XP(const FGameplayAttributeData& OldValue) const {GAMEPLAYATTRIBUTE_REPNOTIFY(ThisClass, XP, OldValue);}

	UFUNCTION()
	FORCEINLINE void OnRep_MaxXP(const FGameplayAttributeData& OldValue) const {GAMEPLAYATTRIBUTE_REPNOTIFY(ThisClass, MaxXP, OldValue);}
	
	UFUNCTION()
	FORCEINLINE void OnRep_Level(const FGameplayAttributeData& OldValue) const {GAMEPLAYATTRIBUTE_REPNOTIFY(ThisClass, Level, OldValue);}
	
	UFUNCTION()
	FORCEINLINE void OnRep_Gold(const FGameplayAttributeData& OldValue) const {GAMEPLAYATTRIBUTE_REPNOTIFY(ThisClass, Gold, OldValue);}

};
