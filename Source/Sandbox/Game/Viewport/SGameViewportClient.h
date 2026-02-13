// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameViewportClient.h"
#include "SGameViewportClient.generated.h"

DECLARE_DYNAMIC_DELEGATE(FOnFadeFinishedSignature);

UCLASS()
class SANDBOX_API USGameViewportClient : public UGameViewportClient
{
	GENERATED_BODY()
public:
	USGameViewportClient();
	
	UFUNCTION(BlueprintCallable, Category = "Fade")
	void StartFade(float InFadeDuration, FLinearColor FadeColor, FOnFadeFinishedSignature OnFadeFinished);

	UFUNCTION(BlueprintCallable, Category = "Fade")
	void StopFade(float InFadeDuration, FOnFadeFinishedSignature OnFadeFinished);
	
protected:
	virtual void DrawTransition(UCanvas* Canvas) override;

private:
	bool bIsFading = false;
	bool bTargetFadeToBlack = false;

	float FadeAlpha = 0.0f;
	float FadeDuration = 1.0f;
	float FadeElapsed = 0.0f;
	float StartAlpha = 0.0f;

	FLinearColor CurrentFadeColor = FLinearColor::Black;

	FOnFadeFinishedSignature FadeFinishedDelegate;
};
