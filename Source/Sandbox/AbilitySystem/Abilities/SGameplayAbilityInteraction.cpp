// Fill out your copyright notice in the Description page of Project Settings.


#include "SGameplayAbilityInteraction.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "Game/Interaction/SWorldInteractionActor.h"

USGameplayAbilityInteraction::USGameplayAbilityInteraction()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
	NetExecutionPolicy = EGameplayAbilityNetExecutionPolicy::ServerOnly;
}

void USGameplayAbilityInteraction::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	const FGameplayEventData* TriggerEventData)
{
	AActor* AvatarActor = ActorInfo->AvatarActor.Get();
	if (!AvatarActor)
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, true, true);
		return;
	}
	
	FVector Start = AvatarActor->GetActorLocation();
	FVector End = Start + AvatarActor->GetActorForwardVector() * InteractionRange;
	
	FHitResult Hit;
	if (AvatarActor->GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECollisionChannel::ECC_Visibility))
	{
		if (ASWorldInteractionActor* InteractionActor = Cast<ASWorldInteractionActor>(Hit.GetActor()))
		{
			if (UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(AvatarActor)->HasAnyMatchingGameplayTags(InteractionActor->InteractionDefinition->RequiredTags) || InteractionActor->InteractionDefinition->RequiredTags.IsEmpty())
			{
				if (!UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(AvatarActor)->HasAnyMatchingGameplayTags(InteractionActor->InteractionDefinition->BlockedTags) || InteractionActor->InteractionDefinition->BlockedTags.IsEmpty())
				{
					InteractionActor->Interact();
					GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Interacted with ") + InteractionActor->GetName());
				}
			}
		}
	}
	
	EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
}
