// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Game/Interaction/SInteractionDefinition.h"
#include "UObject/Interface.h"
#include "SInteractionInterface.generated.h"

// This class does not need to be modified.
UINTERFACE()
class USInteractionInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class SANDBOX_API ISInteractionInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual const USInteractionDefinition* GetInteractionDefinition() const = 0;
	virtual FVector GetInteractionLocation() const = 0;
};
