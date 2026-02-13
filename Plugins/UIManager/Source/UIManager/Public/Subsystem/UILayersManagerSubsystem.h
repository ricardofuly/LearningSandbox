// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Subsystems/LocalPlayerSubsystem.h"
#include "UILayersManagerSubsystem.generated.h"

class UUILayer;

DECLARE_DYNAMIC_DELEGATE_OneParam(FOnWidgetLoaded, UUserWidget*, Widget);

UCLASS()
class UIMANAGER_API UUILayersManagerSubsystem : public ULocalPlayerSubsystem
{
	GENERATED_BODY()
public:
	/** Get subsystem from any WorldContextObject */
	static UUILayersManagerSubsystem* Get(const UObject* WorldContextObject);

	/** Create or retrieve a layer */
	UFUNCTION(BlueprintCallable, Category = "UI Layers")
	UUILayer* CreateLayer(FGameplayTag LayerTag, TSubclassOf<UUILayer> LayerClass);

	/** Pushes a widget onto a specific layer */
	UFUNCTION(BlueprintCallable, Category = "UI Layers")
	UUserWidget* PushToLayer(FGameplayTag LayerTag, TSubclassOf<UUserWidget> WidgetClass, bool ShowMouse = false);

	/** Pushes a widget onto a specific layer. Includes an optional callback function pin to get a reference to the created widget */
	UFUNCTION(BlueprintCallable, Category = "UI Layers")
	void PushToLayerWithCallback(FGameplayTag LayerTag, TSoftClassPtr<UUserWidget> WidgetClass, FOnWidgetLoaded Callback);

	/** Pops a widget from a specific layer if found */
	UFUNCTION(BlueprintCallable, Category = "UI Layers")
	void PopFromLayer(FGameplayTag LayerTag, bool ShowMouse = false);

	/** Clears all widgets in a specific layer if found */
	UFUNCTION(BlueprintCallable, Category = "UI Layers")
	void ClearLayer(FGameplayTag LayerTag);

	/** Clears all widgets all found layers */
	UFUNCTION(BlueprintCallable, Category = "UI Layers")
	void ClearAllLayers();

	/** Clears all widgets in all layers except the one specified */
	UFUNCTION(BlueprintCallable, Category = "UI Layers")
	void ClearAllLayersExcept(FGameplayTag ExceptionLayerTag);

	/** Retrieve an existing layer */
	UFUNCTION(BlueprintCallable, Category = "UI Layers")
	UUILayer* GetLayer(FGameplayTag LayerTag) const;

	/** Remove a layer */
	UFUNCTION(BlueprintCallable, Category = "UI Layers")
	void RemoveLayer(FGameplayTag LayerTag);

private:
	/** All active layers, keyed by tag */
	UPROPERTY(Transient)
	TMap<FGameplayTag, UUILayer*> ActiveLayers;
};
