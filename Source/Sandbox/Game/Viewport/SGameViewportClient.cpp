// Fill out your copyright notice in the Description page of Project Settings.


#include "SGameViewportClient.h"

#include "CanvasItem.h"
#include "Engine/Canvas.h"

USGameViewportClient::USGameViewportClient()
{
}

void USGameViewportClient::StartFade(float InFadeDuration, FLinearColor FadeColor,
	FOnFadeFinishedSignature OnFadeFinished)
{
	bIsFading = true;
	bTargetFadeToBlack = true;

	FadeDuration = FMath::Max(0.01f, InFadeDuration);
	FadeElapsed = 0.0f;
	StartAlpha = FadeAlpha;

	CurrentFadeColor = FadeColor;

	if (OnFadeFinished.IsBound())
	{
		FadeFinishedDelegate = OnFadeFinished;
	}

	bSuppressTransitionMessage = false;
}

void USGameViewportClient::StopFade(float InFadeDuration, FOnFadeFinishedSignature OnFadeFinished)
{
	if (!bIsFading && FadeAlpha <= 0.0f) return;

	bIsFading = true;
	bTargetFadeToBlack = false;

	FadeDuration = FMath::Max(0.01f, InFadeDuration);
	FadeElapsed = 0.0f;
	StartAlpha = FadeAlpha;

	if (OnFadeFinished.IsBound())
	{
		FadeFinishedDelegate = OnFadeFinished;
	}

	bSuppressTransitionMessage = false;
}

void USGameViewportClient::DrawTransition(UCanvas* Canvas)
{
	if (!bIsFading) return;

	FadeElapsed += GetWorld()->GetDeltaSeconds();
	const float Progress = FMath::Clamp(FadeElapsed / FadeDuration, 0.0f, 1.0f);

	if (bTargetFadeToBlack)
	{
		FadeAlpha = FMath::Lerp(StartAlpha, 1.0f, Progress);
	}
	else
	{
		FadeAlpha = FMath::Lerp(StartAlpha, 0.0f, Progress);
	}

	if (FadeAlpha > 0.0f)
	{
		const FLinearColor Color = CurrentFadeColor.CopyWithNewOpacity(FadeAlpha);
		FCanvasTileItem Tile(FVector2D(0, 0), FVector2D(Viewport->GetSizeXY()), Color);
		Tile.BlendMode = SE_BLEND_Translucent;
		Canvas->DrawItem(Tile);
	}

	if (Progress >= 1.0f)
	{
		if (!bTargetFadeToBlack)
		{
			FadeAlpha = 0.0f;
			bSuppressTransitionMessage = true;
		}

		if (FadeFinishedDelegate.IsBound())
		{
			FadeFinishedDelegate.Execute();
			FadeFinishedDelegate.Unbind();
		}
	}
}
