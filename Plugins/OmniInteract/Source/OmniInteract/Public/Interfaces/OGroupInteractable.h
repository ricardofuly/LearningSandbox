// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Types/OTypes.h"
#include "UObject/Interface.h"
#include "OGroupInteractable.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UOGroupInteractable : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class OMNIINTERACT_API IOGroupInteractable
{
	GENERATED_BODY()

public:
	
	// Group Interactions
	// Build interaction options for a group of actors
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void GetGroupInteractionOptions(const TArray<AActor*>& GroupActors, TArray<FInteractionOption>& OutOptions);
	
	// Execute a group interaction (SERVER)
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void InteractGroup(AActor* Interactor, const TArray<AActor*>& GroupActors, int32 OptionIndex);
	
	// Single Interactions
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void GetInteractionData(TArray<FInteractionOption>& OutOptions);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Interact(AActor* Interactor, int32 OptionIndex);
};
