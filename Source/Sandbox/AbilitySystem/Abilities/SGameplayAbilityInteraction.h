// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SGameplayAbility.h"
#include "SGameplayAbilityInteraction.generated.h"

/**
 * 
 */
UCLASS()
class SANDBOX_API USGameplayAbilityInteraction : public USGameplayAbility
{
	GENERATED_BODY()
public:
	USGameplayAbilityInteraction();
	
protected:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float InteractionRange = 200.f;
};
