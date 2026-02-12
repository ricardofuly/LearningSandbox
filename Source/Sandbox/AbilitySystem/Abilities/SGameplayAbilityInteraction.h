// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SGameplayAbility.h"
#include "SGameplayAbilityInteraction.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnGameplayTagAdded, FGameplayTag, Tag);

UCLASS()
class SANDBOX_API USGameplayAbilityInteraction : public USGameplayAbility
{
	GENERATED_BODY()
public:
	USGameplayAbilityInteraction();
	
	UPROPERTY(BlueprintAssignable)
	FOnGameplayTagAdded OnGameplayTagAdded;
	
	UFUNCTION(BlueprintCallable)
	void ListenToRequestedTag(FName TagName);
	
	UFUNCTION()
	void OnTagAdded(FGameplayTag Tag, int32 NewCount);
	
protected:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float InteractionRange = 200.f;
};
