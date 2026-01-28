// Fill out your copyright notice in the Description page of Project Settings.


#include "SGameplayAbilityStackable.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystem/AttributeSet/SStackAttributeSet.h"


void USGameplayAbilityStackable::OnGiveAbility(const FGameplayAbilityActorInfo* ActorInfo,
                                               const FGameplayAbilitySpec& Spec)
{
    Super::OnGiveAbility(ActorInfo, Spec);
    
    // Apply the initial stack effect
    UAbilitySystemComponent* ASC = nullptr;
    if (ActorInfo && ActorInfo->AbilitySystemComponent.IsValid())
    {
        ASC = ActorInfo->AbilitySystemComponent.Get();
    }

    if (!ASC) return;
    
    FGameplayEffectContextHandle ContextHandle = ASC->MakeEffectContext();
    FGameplayEffectSpecHandle SpecHandle = ASC->MakeOutgoingSpec(StackEffect, 1, ContextHandle);
    
    if (SpecHandle.IsValid())
    {
        FGameplayTag DataTag = FGameplayTag::RequestGameplayTag(FName("Data.Ability.Stackable"));
        SpecHandle.Data.Get()->SetSetByCallerMagnitude(DataTag, DefaultStacks);
        
        ASC->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
    }
    // End of stack effect application
    
    // If auto-regain is enabled, apply the regain effect
    if (bAutoRegainStack)
    {
        ASC->ApplyGameplayEffectToSelf(StackRegainEffect.GetDefaultObject(), 1, ContextHandle);
    }
}

void USGameplayAbilityStackable::EndAbility(const FGameplayAbilitySpecHandle Handle,
    const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
    Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

void USGameplayAbilityStackable::ApplyCooldown(const FGameplayAbilitySpecHandle Handle,
    const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo) const
{
    if (UGameplayEffect* CooldownGE = GetCooldownGameplayEffect())
    {
        if (GetASC())
        {
            FGameplayEffectContextHandle ContextHandle = GetASC()->MakeEffectContext();
            FGameplayEffectSpecHandle SpecHandle = GetASC()->MakeOutgoingSpec(CooldownGE->GetClass(), GetAbilityLevel() , ContextHandle);
        
            if ( const USStackAttributeSet* StackAttributes = GetASC()->GetSet<USStackAttributeSet>())
            {
                float CurrentStacks = StackAttributes->GetDashStacks();
            
                if (SpecHandle.IsValid() && CurrentStacks > 1.f)
                {
                    FGameplayTag DataTag = FGameplayTag::RequestGameplayTag(FName("Data.Ability.Dash.Cooldown"));
                    SpecHandle.Data.Get()->SetSetByCallerMagnitude(DataTag, DefaultCooldown);
                }
                else
                {
                    FGameplayTag DataTag = FGameplayTag::RequestGameplayTag(FName("Data.Ability.Dash.Cooldown"));
                    SpecHandle.Data.Get()->SetSetByCallerMagnitude(DataTag, OutOfStacksCooldown);
                }
            }
            ApplyGameplayEffectSpecToOwner(Handle, ActorInfo, ActivationInfo, SpecHandle);
        }
    }
}

UAbilitySystemComponent* USGameplayAbilityStackable::GetASC() const
{
    if (UAbilitySystemComponent* ASC = GetPlayerCharacterFromActorInfo()->GetAbilitySystemComponent())
    {
      return ASC;
    }
    return nullptr;
}
