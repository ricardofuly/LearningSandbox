// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Game/Viewport/SGameViewportClient.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "SCoreFunctions.generated.h"

/**
 * 
 */
UCLASS()
class SANDBOX_API USCoreFunctions : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	
	// Fade
	UFUNCTION(BlueprintCallable, Category = "Gameplay|Viewport", meta = (WorldContext = "WorldContextObject"))
	static void StartFade(UObject* WorldContextObject, float FadeDuration, FLinearColor FadeColor, FOnFadeFinishedSignature OnFadeFinished);

	UFUNCTION(BlueprintCallable, Category = "Gameplay|Viewport", meta = (WorldContext = "WorldContextObject"))
	static void StopFade(UObject* WorldContextObject, float FadeDuration, FOnFadeFinishedSignature OnFadeFinished);
};
