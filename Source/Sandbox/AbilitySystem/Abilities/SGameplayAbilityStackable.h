// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SGameplayAbility.h"
#include "SGameplayAbilityStackable.generated.h"

/**
 * 
 */
UCLASS()
class SANDBOX_API USGameplayAbilityStackable : public USGameplayAbility
{
	GENERATED_BODY()
	
public:
	
	virtual void OnGiveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec) override;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Sandbox | Info")
	int32 AbilityStacks;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Sandbox | Info")
	TSubclassOf<UGameplayEffect> StackEffect;
	
	UFUNCTION(BlueprintCallable, Category="Sandbox|Info")
	FORCEINLINE int32 GetAbilityStack() const { return AbilityStacks; }
};
