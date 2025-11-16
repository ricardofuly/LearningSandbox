// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "AbilitySystem/LAbilitySystemComponent.h"
#include "Player/LPlayerCharacter.h"
#include "Player/LPlayerController.h"
#include "LGameplayAbility.generated.h"

UENUM(BlueprintType)
enum class ESAbilityActivationPolicy : uint8
{
	OnTriggered,
	OnGiven
};

UCLASS()
class LEARNING_API ULGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()
public:
	
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category="Ability Info")
	FName AbilityName;
	
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category="Ability Info")
	FName AbilityDescription;
	
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category="Ability Info")
	TSoftObjectPtr<UTexture2D> AbilityIcon;
	
protected:
	
	UPROPERTY(EditDefaultsOnly, Category="Ability Info")
	ESAbilityActivationPolicy ActivationPolicy = ESAbilityActivationPolicy::OnTriggered;

	
	virtual  void OnGiveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;
	
	UFUNCTION(BlueprintPure, Category="Ability Info")
	ALPlayerCharacter* GetPlayerCharacterFromActorInfo();

	UFUNCTION(BlueprintPure, Category="Ability Info")
	ALPlayerController* GetPlayerControllerFromActorInfo();

	UFUNCTION(BlueprintPure, Category="Ability Info")
	ULAbilitySystemComponent* GetAbilitySystemFromActorInfo() const;

private:
	TWeakObjectPtr<ALPlayerCharacter> CachedPlayerCharacter;
	TWeakObjectPtr<ALPlayerController> CachedPlayerController;
	
};
