// Fill out your copyright notice in the Description page of Project Settings.


#include "SPlayerInitialData.h"

bool FSPlayerAbilitySet::IsValid() const
{
	return AbilityToGrant != nullptr;
}

void USPlayerInitialData::GiveToAbilitySystemComponent(USAbilitySystemComponent* InASCToGive, int32 ApplyLevel) const
{
	check(InASCToGive);

	GrantAbilities(ActiveOnGivenAbilities, InASCToGive, ApplyLevel);
	GrantAbilities(ReactiveAbilities, InASCToGive, ApplyLevel);

	if (!StartUpGameplayEffects.IsEmpty())
	{
		for (const TSubclassOf<UGameplayEffect>& EffectClass : StartUpGameplayEffects)
		{
			if (!EffectClass) continue;

			FGameplayEffectSpecHandle EffectSpecHandle = InASCToGive->MakeOutgoingSpec(EffectClass, ApplyLevel, InASCToGive->MakeEffectContext());
			if (EffectSpecHandle.IsValid())
			{
				InASCToGive->ApplyGameplayEffectSpecToSelf(*EffectSpecHandle.Data.Get());
			}
		}
	}

	for (const FSPlayerAbilitySet& AbilitySet : HeroStartUpAbilitySet)
	{
		if (!AbilitySet.IsValid()) continue;

		FGameplayAbilitySpec AbilitySpec(AbilitySet.AbilityToGrant);
		AbilitySpec.SourceObject = InASCToGive->GetAvatarActor();
		AbilitySpec.Level = ApplyLevel;
		AbilitySpec.GetDynamicSpecSourceTags().AddTag(AbilitySet.InputTag);
		
		InASCToGive->GiveAbility(AbilitySpec);
	}			
}

void USPlayerInitialData::GrantAbilities(const TArray<TSubclassOf<USGameplayAbility>>& InAbilities,
	USAbilitySystemComponent* InASCToGive, int32 ApplyLevel) const
{
	if (InAbilities.IsEmpty()) return;

	for(const TSubclassOf<USGameplayAbility>& Ability : InAbilities)
	{
		if (!Ability) continue;

		FGameplayAbilitySpec AbilitySpec(Ability);
		AbilitySpec.SourceObject = InASCToGive->GetAvatarActor();
		AbilitySpec.Level = ApplyLevel;
		
		InASCToGive->GiveAbility(AbilitySpec);		
	}
}
