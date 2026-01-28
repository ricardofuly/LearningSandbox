// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SGameplayAbility.h"
#include "GameplayEffectTypes.h" // for FActiveGameplayEffectHandle
#include "SGameplayAbilityStackable.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAbilityCommited);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnStackEffectEnded, FActiveGameplayEffectHandle, Handle, int32, RemainingStacks);

UCLASS()
class SANDBOX_API USGameplayAbilityStackable : public USGameplayAbility
{
	GENERATED_BODY()
	
public:
	
	virtual void OnGiveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;
	virtual  void ApplyCooldown(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo) const override;
	
	UAbilitySystemComponent* GetASC() const;
	
	// Default number of stacks to apply when the ability is granted.
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Sandbox | Info")
	int32 DefaultStacks = 3;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Sandbox | Info")
	int32 DefaultCooldown = 3;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Sandbox | Info")
	int32 OutOfStacksCooldown = 10;
	
	// If true, when a stack effect expires the ability will automatically try to regain one stack (up to DefaultStacks).
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Sandbox | Info")
	bool bAutoRegainStack = false;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Sandbox | Info")
	TSubclassOf<UGameplayEffect> StackEffect;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Sandbox | Info")
	TSubclassOf<UGameplayEffect> StackRegainEffect;
};

