// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/AssetManager.h"
#include "LAssetManager.generated.h"

/**
 * 
 */
UCLASS()
class LEARNING_API ULAssetManager : public UAssetManager
{
	GENERATED_BODY()
public:

	ULAssetManager();

	static ULAssetManager& Get();

protected:

	virtual  void StartInitialLoading() override;
};
