// Fill out your copyright notice in the Description page of Project Settings.


#include "SMetaAttributeSet.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "GameplayEffectExtension.h"
#include "Net/UnrealNetwork.h"
#include "Tags/SGameplayTags.h"

USMetaAttributeSet::USMetaAttributeSet()
{
	InitMaxHealth(100.f);
	InitMaxMana(100.f);
	InitMaxStamina(100.f);
	InitGold(0.f);
	InitLevel(1.f);
	InitXP(0.f);
	InitMaxXP(GetRequiredXPForNextLevel());
	
	InitHealth(GetMaxHealth());
	InitMana(GetMaxMana());
	InitStamina(GetMaxStamina());
}

void USMetaAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	DOREPLIFETIME_CONDITION_NOTIFY(ThisClass, Health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(ThisClass, MaxHealth, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(ThisClass, Mana, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(ThisClass, MaxMana, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(ThisClass, Stamina, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(ThisClass, MaxStamina, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(ThisClass, Gold, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(ThisClass, Level, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(ThisClass, XP, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(ThisClass, MaxXP, COND_None, REPNOTIFY_Always);
}

void USMetaAttributeSet::PreAttributeBaseChange(const FGameplayAttribute& Attribute, float& NewValue) const
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
	else if (Attribute == GetMaxManaAttribute())
	{
		float CurrentMana = GetMana();
		if (CurrentMana > NewValue)
		{
			NewValue = CurrentMana;
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
	else if (Attribute == GetXPAttribute())
	{
		if (NewValue < 0.f)
		{
			NewValue = 0.f;
		}		
	}
}

void USMetaAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);
	
	if (Data.EvaluatedData.Attribute == GetHealthAttribute())
	{
		SetHealth(FMath::Clamp(GetHealth(), 0.f, GetMaxHealth()));
		if (GetHealth() <= 0.f)
		{
			FGameplayEventData Payload;
			Payload.Instigator = Data.Target.GetAvatarActor();
		
			UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(Data.Target.GetAvatarActor(), Sandbox::Shared_Event_Killed, Payload);
		}
	}

	if (Data.EvaluatedData.Attribute == GetManaAttribute())
	{
		SetMana(FMath::Clamp(GetMana(), 0.f, GetMaxMana()));
		if (GetMana() <= 0.f)
		{
			FGameplayEventData Payload;
			Payload.Instigator = Data.EffectSpec.GetEffectContext().GetInstigator();
		
			UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(Data.Target.GetAvatarActor(), Sandbox::Shared_Event_NoMana, Payload);
		}
	}

	if (Data.EvaluatedData.Attribute == GetStaminaAttribute())
	{
		SetStamina(FMath::Clamp(GetStamina(), 0.f, GetMaxStamina()));
		if (GetStamina() <= 0.f)
		{
			FGameplayEventData Payload;
			Payload.Instigator = Data.EffectSpec.GetEffectContext().GetInstigator();
		
			UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(Data.Target.GetAvatarActor(), Sandbox::Shared_Event_Exhausted, Payload);
		}
	}
	
	if (Data.EvaluatedData.Attribute == GetXPAttribute())
	{
		FGameplayEventData Payload;
		Payload.Target = Data.EffectSpec.GetEffectContext().GetInstigator();
		
		AddXP(GetXP(), Data, Payload);		
	}

	if (Data.EvaluatedData.Attribute == GetGoldAttribute())
	{
		SetGold(FMath::Max(GetGold(), 0.f));
	}
}

void USMetaAttributeSet::AddXP(float Amount, const FGameplayEffectModCallbackData& Data,
	const FGameplayEventData& Payload)
{
	float CurrentXP = GetXP();
	float CurrentLevel = GetLevel();
 
	CurrentXP += Amount;
 
	while (CurrentXP >= GetRequiredXPForNextLevel())
	{
		CurrentXP -= GetRequiredXPForNextLevel();
		CurrentLevel += 1.f;

		UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(Data.Target.GetAvatarActor(), Sandbox::Player_Event_LevelUp, Payload);
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Leveled Up! New Level: %d, %s"), FMath::FloorToInt(CurrentLevel), *Data.Target.GetAvatarActor()->GetName()));
	}
 
	SetXP(CurrentXP);
	SetMaxXP(GetRequiredXPForNextLevel());
	SetLevel(CurrentLevel);
}

float USMetaAttributeSet::GetRequiredXPForNextLevel() const
{
	return 200.f * FMath::Pow(1.15f, GetLevel());
}
