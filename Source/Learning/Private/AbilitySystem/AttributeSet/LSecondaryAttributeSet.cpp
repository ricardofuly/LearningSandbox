// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/AttributeSet/LSecondaryAttributeSet.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "GameplayEffectExtension.h"
#include "Net/UnrealNetwork.h"

ULSecondaryAttributeSet::ULSecondaryAttributeSet()
{
}

void ULSecondaryAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	DOREPLIFETIME_CONDITION_NOTIFY(ThisClass, Defense, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(ThisClass, MagicDefense, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(ThisClass, SlashStrength, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(ThisClass, SlashResistance, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(ThisClass, StrikeStrength, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(ThisClass, StrikeResistance, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(ThisClass, KnockdownPower, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(ThisClass, KnockdownResistance, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(ThisClass, XP, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(ThisClass, Level, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(ThisClass, Gold, COND_None, REPNOTIFY_Always);		
}

void ULSecondaryAttributeSet::PreAttributeBaseChange(const FGameplayAttribute& Attribute, float& NewValue) const
{
	Super::PreAttributeBaseChange(Attribute, NewValue);
}

void ULSecondaryAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	if (Data.EvaluatedData.Attribute == GetDefenseAttribute())
	{
		SetDefense(FMath::Clamp(GetDefense(), 0.f, GetDefense()));
	}
	
	if (Data.EvaluatedData.Attribute == GetMagicDefenseAttribute())
	{
		SetMagicDefense(FMath::Clamp(GetMagicDefense(), 0.f, GetMagicDefense()));
	}

	if (Data.EvaluatedData.Attribute == GetSlashStrengthAttribute())
	{
		SetSlashStrength(FMath::Clamp(GetSlashStrength(), 0.f, GetSlashStrength()));
	}
	
	if (Data.EvaluatedData.Attribute == GetSlashResistanceAttribute())
	{
		SetSlashResistance(FMath::Clamp(GetSlashResistance(), 0.f, GetSlashResistance()));
	}
	
	if (Data.EvaluatedData.Attribute == GetStrikeStrengthAttribute())
	{
		SetStrikeStrength(FMath::Clamp(GetStrikeStrength(), 0.f, GetStrikeStrength()));
	}
	
	if (Data.EvaluatedData.Attribute == GetStrikeResistanceAttribute())
	{
		SetStrikeResistance(FMath::Clamp(GetStrikeResistance(), 0.f, GetStrikeResistance()));
	}
	
	if (Data.EvaluatedData.Attribute == GetKnockdownPowerAttribute())
	{
		SetKnockdownPower(FMath::Clamp(GetKnockdownPower(), 0.f, GetKnockdownPower()));
	}
	
	if (Data.EvaluatedData.Attribute == GetKnockdownResistanceAttribute())
	{
		SetKnockdownResistance(FMath::Clamp(GetKnockdownResistance(), 0.f, GetKnockdownResistance()));
	}
	
	if (Data.EvaluatedData.Attribute == GetXPAttribute())
	{
		SetXP(FMath::Clamp(GetXP(), 0.f, GetRequiredXPForNextLevel()));
	}
	
	if (Data.EvaluatedData.Attribute == GetLevelAttribute())
	{
		SetLevel(FMath::Clamp(GetLevel(), 0.f, GetLevel() + 1.f));
	}
	
	if (Data.EvaluatedData.Attribute == GetGoldAttribute())
	{
		SetGold(FMath::Clamp(GetGold(), 0.f, GetGold() + 1.f));
	}
}

void ULSecondaryAttributeSet::AddXP(float Amount, const FGameplayEffectModCallbackData& Data)
{
	float CurrentXP = GetXP();
	float CurrentLevel = GetLevel();
 
	CurrentXP += Amount;
 
	while (CurrentXP >= GetRequiredXPForNextLevel())
	{
		CurrentXP -= GetRequiredXPForNextLevel();
		CurrentLevel += 1.f;
		
		FGameplayEventData Payload;
		Payload.Target = Data.Target.GetAvatarActor();
		Payload.EventTag = FGameplayTag::RequestGameplayTag(FName("Events.LevelUp")); 

		UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(Data.EffectSpec.GetEffectContext().GetInstigator(), Payload.EventTag, Payload);
	}
 
	SetXP(CurrentXP);
	SetLevel(CurrentLevel);
}

float ULSecondaryAttributeSet::GetRequiredXPForNextLevel() const
{
	return FMath::Pow(2.5f, GetLevel()) * 100.f;
}
