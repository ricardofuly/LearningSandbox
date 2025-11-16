// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffect.h"
#include "LGameplayEffect.generated.h"

/**
 * 
 */
UCLASS()
class LEARNING_API ULGameplayEffect : public UGameplayEffect
{
	GENERATED_BODY()
public:
	
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category="Effect Info")
	FName EffectName;
	
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category="Effect Info")
	FName EffectDescription;
	
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category="Effect Info")
	TSoftObjectPtr<UTexture2D> EffectIcon;
	
};
