// Fill out your copyright notice in the Description page of Project Settings.


#include "SSecondaryAttributeSet.h"

#include "Net/UnrealNetwork.h"

USSecondaryAttributeSet::USSecondaryAttributeSet()
{
	InitDefense(5.f);
	InitEndurance(0.f);
	InitFireResistance(5.f);
	InitIceResistance(5.f);
	InitChaosResistance(5.f);
	InitAllElementalResistance(5.f);
}

void USSecondaryAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	DOREPLIFETIME_CONDITION_NOTIFY(ThisClass, Defense, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(ThisClass, Endurance, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(ThisClass, FireResistance, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(ThisClass, IceResistance, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(ThisClass, ChaosResistance, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(ThisClass, AllElementalResistance, COND_None, REPNOTIFY_Always);
}

void USSecondaryAttributeSet::PreAttributeBaseChange(const FGameplayAttribute& Attribute, float& NewValue) const
{
	Super::PreAttributeBaseChange(Attribute, NewValue);
}

void USSecondaryAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);
}
