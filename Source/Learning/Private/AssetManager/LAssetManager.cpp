// Fill out your copyright notice in the Description page of Project Settings.


#include "AssetManager/LAssetManager.h"

#include "Tags/LGameplayTags.h"

ULAssetManager::ULAssetManager()
{
}

ULAssetManager& ULAssetManager::Get()
{
	check(GEngine);
 
	ULAssetManager* MyAssetManager = Cast<ULAssetManager>(GEngine->AssetManager);
	return *MyAssetManager;
}

void ULAssetManager::StartInitialLoading()
{
	Super::StartInitialLoading();

	// Load Gameplay Tags
	FGameplayTags::InitializeNativeTags();
}
