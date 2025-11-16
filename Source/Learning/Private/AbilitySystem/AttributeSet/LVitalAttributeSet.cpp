// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/AttributeSet/LVitalAttributeSet.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "GameplayEffectExtension.h"
#include "Net/UnrealNetwork.h"

ULVitalAttributeSet::ULVitalAttributeSet()
{
}

void ULVitalAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	DOREPLIFETIME_CONDITION_NOTIFY(ThisClass, Health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(ThisClass, MaxHealth, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(ThisClass, Stamina, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(ThisClass, MaxStamina, COND_None, REPNOTIFY_Always);
}

void ULVitalAttributeSet::PreAttributeBaseChange(const FGameplayAttribute& Attribute, float& NewValue) const
{
	Super::PreAttributeBaseChange(Attribute, NewValue);

	if (Attribute == GetMaxHealthAttribute())
	{
		float CurrentHealth = GetHealth();
		if (CurrentHealth > NewValue)
		{
			NewValue = CurrentHealth;
		}
	}
	else if (Attribute == GetMaxStaminaAttribute())
	{
		float CurrentStamina = GetStamina();
		if (CurrentStamina > NewValue)
		{
			NewValue = CurrentStamina;
		}
	}
}

void ULVitalAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	if (Data.EvaluatedData.Attribute == GetHealthAttribute())
	{
		SetHealth(FMath::Clamp(GetHealth(), 0.f, GetMaxHealth()));

		if (GetHealth() <= 0.f)
		{
			FGameplayEventData Payload;
			Payload.EventTag = FGameplayTag::RequestGameplayTag(FName("Events.Death"));
			Payload.Instigator = Data.Target.GetAvatarActor();
			
			UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(Data.EffectSpec.GetEffectContext().GetInstigator(), Payload.EventTag, Payload);
		}
	}
	
	if (Data.EvaluatedData.Attribute == GetStaminaAttribute())
	{
		SetStamina(FMath::Clamp(GetStamina(), 0.f, GetMaxStamina()));

		if (GetStamina() <= 0.f)
		{
			FGameplayEventData Payload;
			Payload.EventTag = FGameplayTag::RequestGameplayTag(FName("Events.Panting"));
			
			UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(Data.EffectSpec.GetEffectContext().GetInstigator(), Payload.EventTag, Payload);
		}
	}	
}
