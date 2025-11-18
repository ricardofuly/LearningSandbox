// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "AttributeSet.h"
#include "AbilitySystem/SAbilitySystemComponent.h"
#include "AbilitySystem/AttributeSet/SMetaAttributeSet.h"
#include "AbilitySystem/AttributeSet/SPrimaryAttributeSet.h"
#include "AbilitySystem/AttributeSet/SSecondaryAttributeSet.h"
#include "GameFramework/PlayerState.h"
#include "SPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class SANDBOX_API ASPlayerState : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()
public:
	ASPlayerState();
	
	virtual void OnPossess(APawn* InPawn);
	virtual void OnRep_PlayerState();
	
	virtual USAbilitySystemComponent* GetAbilitySystemComponent() const override;
	TArray<TObjectPtr<USAttributeSetBase>> GetAttributeSet() const;
	
protected:
	
	virtual void BeginPlay() override;
	
private:
	
	UPROPERTY(VisibleAnywhere, Category = "Sandbox | AbilitySystem")
	TObjectPtr<USAbilitySystemComponent> AbilitySystemComponent;
	
	UPROPERTY()
	TObjectPtr<USMetaAttributeSet> MetaAttributeSet;
	
	UPROPERTY()
	TObjectPtr<USPrimaryAttributeSet> PrimaryAttributeSet;
	
	UPROPERTY()
	TObjectPtr<USSecondaryAttributeSet> SecondaryAttributeSet;
	
	UPROPERTY(EditAnywhere, Category = "Sandbox | AbilitySystem")
	EGameplayEffectReplicationMode ReplicationMode = EGameplayEffectReplicationMode::Mixed;
};
