// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "AbilitySystem/LAbilitySystemComponent.h"
#include "GameFramework/PlayerState.h"
#include "LPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class LEARNING_API ALPlayerState : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()
public:
	ALPlayerState();

	virtual void OnPossess(APawn* InPawn);
	virtual void OnRep_PlayerState();

	virtual ULAbilitySystemComponent* GetAbilitySystemComponent() const override { return AbilitySystemComponent;}

protected:
	virtual void BeginPlay() override;

private:

	UPROPERTY(VisibleAnywhere, Category = "Learning|AbilitySystem")
	TObjectPtr<ULAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY(VisibleAnywhere, Category = "Learning|AbilitySystem")
	EGameplayEffectReplicationMode ReplicationMode = EGameplayEffectReplicationMode::Mixed;
};
