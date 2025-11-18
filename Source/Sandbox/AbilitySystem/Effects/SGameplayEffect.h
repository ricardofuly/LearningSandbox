// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffect.h"
#include "SGameplayEffect.generated.h"

/**
 * 
 */
UCLASS()
class SANDBOX_API USGameplayEffect : public UGameplayEffect
{
	GENERATED_BODY()
public:
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Sandbox | Info")
	FText EffectName;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Sandbox | Info")
	FText EffectDescription;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Sandbox | Info")
	TObjectPtr<UTexture2D> EffectIcon;
};
