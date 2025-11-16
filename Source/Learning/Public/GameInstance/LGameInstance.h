// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ShaderPipelineCache.h"
#include "Engine/GameInstance.h"
#include "LGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class LEARNING_API ULGameInstance : public UGameInstance
{
	GENERATED_BODY()
public:
	virtual void Init() override;
	virtual void Shutdown() override;

protected:
	void OnPrecompileStart(uint32 Count, const FShaderPipelineCache::FShaderCachePrecompileContext& Context);
	void OnPrecompileEnd(uint32 Count, double Time, const FShaderPipelineCache::FShaderCachePrecompileContext& Context);

private:

	UPROPERTY()
	TSubclassOf<UUserWidget> PrecompileWidget;

	UUserWidget* PrecompileWidgetInstance;
};
