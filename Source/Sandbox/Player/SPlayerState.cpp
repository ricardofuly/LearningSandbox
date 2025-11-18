// Fill out your copyright notice in the Description page of Project Settings.


#include "SPlayerState.h"

ASPlayerState::ASPlayerState()
{
	AbilitySystemComponent = CreateDefaultSubobject<USAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(ReplicationMode);

	MetaAttributeSet = CreateDefaultSubobject<USMetaAttributeSet>("MetaAttributeSet");
	PrimaryAttributeSet = CreateDefaultSubobject<USPrimaryAttributeSet>("PrimaryAttributeSet");
	SecondaryAttributeSet = CreateDefaultSubobject<USSecondaryAttributeSet>("SecondaryAttributeSet");
}

void ASPlayerState::OnPossess(APawn* InPawn)
{
	if (IsValid(AbilitySystemComponent) && IsValid(InPawn))
	{
		AbilitySystemComponent->InitAbilityActorInfo(this, InPawn);
	}
}

void ASPlayerState::OnRep_PlayerState()
{
	if (IsValid(AbilitySystemComponent) && IsValid(GetPawn()))
	{
		AbilitySystemComponent->InitAbilityActorInfo(this, GetPawn());
	}
}

USAbilitySystemComponent* ASPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

TArray<TObjectPtr<USAttributeSetBase>> ASPlayerState::GetAttributeSet() const
{
	TArray<TObjectPtr<USAttributeSetBase>> AttributeSets;
	AttributeSets.Add(MetaAttributeSet);
	AttributeSets.Add(PrimaryAttributeSet);
	AttributeSets.Add(SecondaryAttributeSet);
	
	return AttributeSets;
}

void ASPlayerState::BeginPlay()
{
	Super::BeginPlay();

	// Initialize Abilities and Effects
	if (!PlayerInitialData->InitialAbilities.IsEmpty())
	{
		for (TObjectPtr<UGameplayAbility> Ability : PlayerInitialData->InitialAbilities)
		{
			if (IsValid(AbilitySystemComponent) && IsValid(Ability))
			{
				AbilitySystemComponent->GiveAbility(FGameplayAbilitySpec(Ability, MetaAttributeSet->GetPlayerLevel()));
			}
		}
	}

	if (!PlayerInitialData->InitialEffects.IsEmpty())
	{
		for (TSubclassOf<UGameplayEffect> EffectClass : PlayerInitialData->InitialEffects)
		{
			if (IsValid(AbilitySystemComponent) && *EffectClass)
			{
				FGameplayEffectContextHandle EffectContext = AbilitySystemComponent->MakeEffectContext();
				EffectContext.AddSourceObject(this);

				FGameplayEffectSpecHandle SpecHandle = AbilitySystemComponent->MakeOutgoingSpec(EffectClass, MetaAttributeSet->GetPlayerLevel(), EffectContext);
				if (SpecHandle.IsValid())
				{
					AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
				}
			}
		}
	}
}
