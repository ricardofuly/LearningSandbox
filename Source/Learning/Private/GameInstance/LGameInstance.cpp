// Fill out your copyright notice in the Description page of Project Settings.


#include "GameInstance/LGameInstance.h"

#include "Blueprint/UserWidget.h"
#include "DeveloperSettings/LDeveloperSettings.h"

void ULGameInstance::Init()
{
	Super::Init();

	FShaderPipelineCache::GetPrecompilationBeginDelegate().AddUObject(this, &ULGameInstance::OnPrecompileStart);
	FShaderPipelineCache::GetPrecompilationCompleteDelegate().AddUObject(this, &ULGameInstance::OnPrecompileEnd);

	const ULDeveloperSettings* DeveloperSettings = GetDefault<ULDeveloperSettings>();
	PrecompileWidget = DeveloperSettings->PrecompileWidget;
}

void ULGameInstance::Shutdown()
{
	FShaderPipelineCache::GetPrecompilationBeginDelegate().RemoveAll(this);
	FShaderPipelineCache::GetPrecompilationCompleteDelegate().RemoveAll(this);
	
	Super::Shutdown();
	
}

void ULGameInstance::OnPrecompileStart(uint32 Count, const FShaderPipelineCache::FShaderCachePrecompileContext& Context)
{
	if (!PrecompileWidget)
	{
		UE_LOG(LogTemp, Warning, TEXT("Precompile Widget não está configurado nas Developer Settings"));
		return;
	}
	
	UWorld* World = GetWorld();
	if (!World)
	{
		return;
	}
	
	PrecompileWidgetInstance = CreateWidget<UUserWidget>(World, PrecompileWidget);
	if (PrecompileWidgetInstance)
	{
		PrecompileWidgetInstance->AddToViewport();
	}
}

void ULGameInstance::OnPrecompileEnd(uint32 Count, double Time, const FShaderPipelineCache::FShaderCachePrecompileContext& Context)
{
	PrecompileWidgetInstance->RemoveFromParent();
}
