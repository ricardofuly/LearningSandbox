// Fill out your copyright notice in the Description page of Project Settings.


#include "SGameplayAbility.h"

#include "AbilitySystem/AttributeSet/SMetaAttributeSet.h"

void USGameplayAbility::OnGiveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec)
{
    Super::OnGiveAbility(ActorInfo, Spec);
    
    if (ActivationPolicy == ESAbilityActivationPolicy::OnGiven)
    {
        if (ActorInfo != nullptr && !Spec.IsActive())
        {
            if (ActorInfo->AbilitySystemComponent.IsValid())
            {
                ActorInfo->AbilitySystemComponent.Get()->TryActivateAbility(Spec.Handle);
            }
        }
    }
}

void USGameplayAbility::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
    const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
    Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
    
    if (ActivationPolicy == ESAbilityActivationPolicy::OnGiven)
    {
        if (ActorInfo != nullptr && ActorInfo->AbilitySystemComponent.IsValid())
        {
            ActorInfo->AbilitySystemComponent.Get()->ClearAbility(Handle);
        }
    }
}

ASandboxCharacter* USGameplayAbility::GetPlayerCharacterFromActorInfo() const 
{
    if (CurrentActorInfo && CurrentActorInfo->AvatarActor.IsValid())
    {
        return  Cast<ASandboxCharacter>(CurrentActorInfo->AvatarActor.Get());
    }
  
    return nullptr;
}

ASandboxPlayerController* USGameplayAbility::GetPlayerControllerFromActorInfo() const
{
    if (CurrentActorInfo && CurrentActorInfo->PlayerController.IsValid())
    {
        return  Cast<ASandboxPlayerController>(CurrentActorInfo->PlayerController.Get());
    }
  
    return nullptr;
}

USAbilitySystemComponent* USGameplayAbility::GetAbilitySystemFromActorInfo() const
{
    if (!CurrentActorInfo)
    {
        return nullptr;
    }

    if (!CurrentActorInfo->AbilitySystemComponent.IsValid())
    {
        return nullptr;
    }

    return Cast<USAbilitySystemComponent>(CurrentActorInfo->AbilitySystemComponent.Get());
}

float USGameplayAbility::GetAvatarActorLevel() const
{
    USAbilitySystemComponent* ASC = GetAbilitySystemFromActorInfo();
    if (!ASC)
    {
        return 0.0f;
    }
    
    if (ASC->GetAttributeSet(USMetaAttributeSet::StaticClass()))
    {
        return ASC->GetNumericAttribute(USMetaAttributeSet::GetLevelAttribute());
    }

    return 0.0f;
}
