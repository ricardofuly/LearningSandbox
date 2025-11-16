// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/AttributeSet/LPrimaryAttributeSet.h"

#include "GameplayEffectExtension.h"
#include "Net/UnrealNetwork.h"

ULPrimaryAttributeSet::ULPrimaryAttributeSet()
{
}

void ULPrimaryAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	DOREPLIFETIME_CONDITION_NOTIFY(ThisClass, Strength, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(ThisClass, Magic, COND_None, REPNOTIFY_Always);
}

void ULPrimaryAttributeSet::PreAttributeBaseChange(const FGameplayAttribute& Attribute, float& NewValue) const
{
	Super::PreAttributeBaseChange(Attribute, NewValue);

	if (Attribute == GetStrengthAttribute())
	{
		if (NewValue < 0.f)
		{
			NewValue = 0.f;
		}
	}
	else if (Attribute == GetMagicAttribute())
	{
		if (NewValue < 0.f)
		{
			NewValue = 0.f;
		}
	}
}

void ULPrimaryAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	if (Data.EvaluatedData.Attribute == GetStrengthAttribute())
	{
		SetStrength(FMath::Clamp(GetStrength(), 0.f, GetStrength()));
	}
	else if (Data.EvaluatedData.Attribute == GetMagicAttribute())
	{
		SetMagic(FMath::Clamp(GetMagic(), 0.f, GetMagic()));
	}
}
