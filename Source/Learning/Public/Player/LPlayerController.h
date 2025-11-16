// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/LInputConfig.h"
#include "GameFramework/PlayerController.h"
#include "LPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class LEARNING_API ALPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;
	virtual void OnPossess(APawn* InPawn) override;
	virtual void OnRep_PlayerState() override;

protected:
	virtual void SetupInputComponent() override;

	// Input Function Handlers
	void HandleMove(const FInputActionValue& InputActionValue);
	void HandleLook(const FInputActionValue& InputActionValue);

	void AbilityInputPressed(FGameplayTag InputTag);
	void AbilityInputReleased(FGameplayTag InputTag);

	void TurnAtRate(float Rate);
	void LookUpAtRate(float Rate);

private:

	UPROPERTY(EditDefaultsOnly, Category= "Input")
	ULInputConfig* InputConfig;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	float TurnRateGamepad = 45.f;
};


