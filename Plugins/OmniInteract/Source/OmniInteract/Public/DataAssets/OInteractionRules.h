// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Types/OTypes.h"
#include "OInteractionRules.generated.h"

struct FInteractionGroupRules;
/**
 * 
 */
UCLASS()
class OMNIINTERACT_API UOInteractionRules : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere)
	TArray<FInteractionGroupRules> Rules;


	const FInteractionGroupRules* GetRulesForClass(TSubclassOf<AActor> Class) const
	{
		for (const FInteractionGroupRules& Rule : Rules)
		{
			if (Rule.ActorClass == Class)
			{
				return &Rule;
			}
		}
		return nullptr;
	}
};
