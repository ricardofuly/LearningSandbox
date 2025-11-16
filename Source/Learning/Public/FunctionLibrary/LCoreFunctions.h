// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "LCoreFunctions.generated.h"

/**
 * 
 */
UCLASS()
class LEARNING_API ULCoreFunctions : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

	UFUNCTION(BlueprintCallable, Category="Core")
	static int32 NumPrecompilePSORemaining();

	UFUNCTION(BlueprintCallable, Category="Core")
	static void ClearPSOCache();
};
