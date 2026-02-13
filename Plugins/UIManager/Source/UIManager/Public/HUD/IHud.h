// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "GameFramework/HUD.h"
#include "Widgets/UILayer.h"
#include "IHud.generated.h"

/**
 * 
 */
UCLASS()
class UIMANAGER_API AIHud : public AHUD
{
	GENERATED_BODY()
protected:
	/** Define layers */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UI")
	TMap<FGameplayTag, TSubclassOf<UUILayer>> LayerDefinitions;

	/** Define optional default widgets */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UI")
	TMap<FGameplayTag, TSoftClassPtr<UUserWidget>> InitialWidgets;

	virtual void BeginPlay() override;

private:
	void InitializeLayout();
};
