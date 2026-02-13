// Fill out your copyright notice in the Description page of Project Settings.


#include "SCoreFunctions.h"

void USCoreFunctions::StartFade(UObject* WorldContextObject, float FadeDuration, FLinearColor FadeColor,
	FOnFadeFinishedSignature OnFadeFinished)
{
	if (!WorldContextObject) return;

	if (UGameViewportClient* ViewportClient = WorldContextObject->GetWorld()->GetGameViewport())
	{
		if (USGameViewportClient* BoneViewportClient = Cast<USGameViewportClient>(ViewportClient))
		{
			BoneViewportClient->StartFade(FadeDuration, FadeColor, OnFadeFinished);
		}
	}
}

void USCoreFunctions::StopFade(UObject* WorldContextObject, float FadeDuration, FOnFadeFinishedSignature OnFadeFinished)
{
	if (!WorldContextObject) return;

	if (UGameViewportClient* ViewportClient = WorldContextObject->GetWorld()->GetGameViewport())
	{
		if (USGameViewportClient* BoneViewportClient = Cast<USGameViewportClient>(ViewportClient))
		{
			BoneViewportClient->StopFade(FadeDuration, OnFadeFinished);
		}
	}
}
