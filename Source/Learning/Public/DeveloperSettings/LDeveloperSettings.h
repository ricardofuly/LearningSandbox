// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "LDeveloperSettings.generated.h"

/**
 * 
 */
UCLASS(Config= "Game", DefaultConfig, meta=(DisplayName = "Developer Settings"))
class LEARNING_API ULDeveloperSettings : public UDeveloperSettings
{
	GENERATED_BODY()
public:

	UPROPERTY(Config, EditAnywhere, Category = "Precompile Widget")
	TSubclassOf<UUserWidget> PrecompileWidget;
};
