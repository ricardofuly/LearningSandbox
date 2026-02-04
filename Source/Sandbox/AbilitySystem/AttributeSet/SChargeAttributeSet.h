// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "SAttributeSetBase.h"
#include "SChargeAttributeSet.generated.h"

/**
 * 
 */
UCLASS()
class SANDBOX_API USChargeAttributeSet : public USAttributeSetBase
{
	GENERATED_BODY()
	
public:
	USChargeAttributeSet();
	
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	virtual void PreAttributeBaseChange(const FGameplayAttribute& Attribute, float& NewValue) const override;
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;
	
	// Attributes
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_FireBallCharge)
	FGameplayAttributeData FireBallCharge;
	ATTRIBUTE_ACCESSORS(ThisClass, FireBallCharge);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxFireBallCharge)
	FGameplayAttributeData MaxFireBallCharge;
	ATTRIBUTE_ACCESSORS(ThisClass, MaxFireBallCharge);
	
protected:
	
	UFUNCTION()
	FORCEINLINE void OnRep_FireBallCharge(const FGameplayAttributeData& OldValue) const {GAMEPLAYATTRIBUTE_REPNOTIFY(ThisClass, FireBallCharge, OldValue);}

	UFUNCTION()
	FORCEINLINE void OnRep_MaxFireBallCharge(const FGameplayAttributeData& OldValue) const {GAMEPLAYATTRIBUTE_REPNOTIFY(ThisClass, MaxFireBallCharge, OldValue);}
};
