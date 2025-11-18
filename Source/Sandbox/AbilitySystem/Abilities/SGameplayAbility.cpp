// Fill out your copyright notice in the Description page of Project Settings.


#include "SGameplayAbility.h"

void USGameplayAbility::OnGiveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec)
{
	Super::OnGiveAbility(ActorInfo, Spec);
	
	if (ActivationPolicy == ESAbilityActivationPolicy::OnGiven)
	{
		if (ActorInfo && !Spec.IsActive())
		{
			ActorInfo->AbilitySystemComponent->TryActivateAbility(Spec.Handle);
		}
	}
}

void USGameplayAbility::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
	
	if (ActivationPolicy == ESAbilityActivationPolicy::OnGiven)
	{
		if (ActorInfo)
		{
			ActorInfo->AbilitySystemComponent->ClearAbility(Handle);
		}
	}
}

ASandboxCharacter* USGameplayAbility::GetPlayerCharacterFromActorInfo()
{
	if (!CachedPlayerCharacter.IsValid())
	{
		CachedPlayerCharacter = Cast<ASandboxCharacter>(CurrentActorInfo->AvatarActor);
	}
	return CachedPlayerCharacter.IsValid() ? CachedPlayerCharacter.Get() : nullptr;
}

ASandboxPlayerController* USGameplayAbility::GetPlayerControllerFromActorInfo()
{
	if (!CachedPlayerController.IsValid())
	{
		CachedPlayerController = Cast<ASandboxPlayerController>(CurrentActorInfo->PlayerController);
	}
	return CachedPlayerController.IsValid() ? CachedPlayerController.Get() : nullptr;
}

USAbilitySystemComponent* USGameplayAbility::GetAbilitySystemFromActorInfo() const
{
	return Cast<USAbilitySystemComponent>(CurrentActorInfo->AbilitySystemComponent);
}
