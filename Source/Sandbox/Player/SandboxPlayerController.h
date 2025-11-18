// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "InputActionValue.h"
#include "Data/Input/SInputConfig.h"
#include "GameFramework/PlayerController.h"
#include "SandboxPlayerController.generated.h"

class UInputMappingContext;
class UUserWidget;

/**
 *  Basic PlayerController class for a third person game
 *  Manages input mappings
 */
UCLASS(abstract)
class ASandboxPlayerController : public APlayerController
{
	GENERATED_BODY()
	
protected:
	
	/** Gameplay initialization */
	virtual void BeginPlay() override;

	/** Input mapping context setup */
	virtual void SetupInputComponent() override;
	
	void HandleMoveInput(const FInputActionValue& Value);
	void HandleLookInput(const FInputActionValue& Value);
	void AbilityInputPressed(FGameplayTag InInputTag);
	void AbilityInputReleased(FGameplayTag InInputTag);
	
private:
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Character Data", meta = (AllowPrivateAccess = "true"))
	USInputConfig* InputConfig;
	
};
