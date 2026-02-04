// Fill out your copyright notice in the Description page of Project Settings.


#include "SStackAttributeSet.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "GameplayEffectExtension.h"
#include "Net/UnrealNetwork.h"
#include "Tags/SGameplayTags.h"

USStackAttributeSet::USStackAttributeSet()
{
	InitDashStacks(0.f);
	InitDashMaxStacks(3.f);
	InitFireBallStacks(0.f);
	InitFireBallMaxStacks(3.f);
}

void USStackAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	DOREPLIFETIME_CONDITION_NOTIFY(ThisClass, DashStacks, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(ThisClass, DashMaxStacks, COND_None, REPNOTIFY_Always);
}

void USStackAttributeSet::PreAttributeBaseChange(const FGameplayAttribute& Attribute, float& NewValue) const
{
	Super::PreAttributeBaseChange(Attribute, NewValue);

	if (Attribute == GetDashMaxStacksAttribute())
	{
		float CurrentDashStacks = GetDashStacks();
		if (CurrentDashStacks > NewValue)
		{
			NewValue = CurrentDashStacks;
		}
	}

	if (Attribute == GetFireBallMaxStacksAttribute())
	{
		float CurrentFireBallStacks = GetFireBallStacks();
		if (CurrentFireBallStacks > NewValue)
		{
			NewValue = CurrentFireBallStacks;
		}
	}
}

void USStackAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);
	
	if (Data.EvaluatedData.Attribute == GetDashStacksAttribute())
	{
		SetDashStacks(FMath::Clamp(GetDashStacks(), 0.f, GetDashMaxStacks()));
		if (GetDashStacks() <= 0.f)
		{
			FGameplayEventData Payload;
			Payload.Instigator = Data.Target.GetAvatarActor();
		
			UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(Data.EffectSpec.GetEffectContext().GetInstigator(), Sandbox::Shared_Event_NoDash, Payload);
		}
	}

	if (Data.EvaluatedData.Attribute == GetFireBallMaxStacksAttribute())
	{
		SetFireBallStacks(FMath::Clamp(GetFireBallStacks(), 0.f, GetFireBallMaxStacks()));
		if (GetFireBallStacks() <= 0.f)
		{
			FGameplayEventData Payload;
			Payload.Instigator = Data.Target.GetAvatarActor();
		
			UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(Data.EffectSpec.GetEffectContext().GetInstigator(), Sandbox::Shared_Event_NoFireBall, Payload);
		}
	}
}
