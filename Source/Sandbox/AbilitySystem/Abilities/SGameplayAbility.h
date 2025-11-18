// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "AbilitySystem/SAbilitySystemComponent.h"
#include "Player/SandboxCharacter.h"
#include "Player/SandboxPlayerController.h"
#include "SGameplayAbility.generated.h"

UENUM(BlueprintType)
enum class ESAbilityActivationPolicy : uint8
{
	OnTriggered,
	OnGiven
};

UCLASS()
class SANDBOX_API USGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()
public:
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Sandbox | Info")
	FText AbilityName;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Sandbox | Info")
	FText AbilityDescription;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Sandbox | Info")
	TObjectPtr<UTexture2D> AbilityIcon;
	
protected:
	UPROPERTY(EditDefaultsOnly, Category="Sandbox | Ability")
	ESAbilityActivationPolicy ActivationPolicy = ESAbilityActivationPolicy::OnTriggered;

	
	virtual  void OnGiveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;
	
	UFUNCTION(BlueprintPure, Category="Sandbox | Ability")
	ASandboxCharacter* GetPlayerCharacterFromActorInfo();

	UFUNCTION(BlueprintPure, Category="Sandbox | Ability")
	ASandboxPlayerController* GetPlayerControllerFromActorInfo();

	UFUNCTION(BlueprintPure, Category="Sandbox | Ability")
	USAbilitySystemComponent* GetAbilitySystemFromActorInfo() const;

private:
	TWeakObjectPtr<ASandboxCharacter> CachedPlayerCharacter;
	TWeakObjectPtr<ASandboxPlayerController> CachedPlayerController;
};
