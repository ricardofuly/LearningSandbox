// Fill out your copyright notice in the Description page of Project Settings.


#include "SGameplayAbilityStackable.h"

#include "AbilitySystemBlueprintLibrary.h"

void USGameplayAbilityStackable::OnGiveAbility(const FGameplayAbilityActorInfo* ActorInfo,
                                               const FGameplayAbilitySpec& Spec)
{
	Super::OnGiveAbility(ActorInfo, Spec);

	for (int i = 0; i < AbilityStacks; ++i)
	{
		GetAbilitySystemFromActorInfo()->ApplyGameplayEffectToSelf(StackEffect->GetDefaultObject<UGameplayEffect>(), 1, GetAbilitySystemFromActorInfo()->MakeEffectContext());
	}
}
