// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "InputAction.h"
#include "InputMappingContext.h"
#include "Engine/DataAsset.h"
#include "SInputConfig.generated.h"

USTRUCT(BlueprintType)
struct FSInputActionConfig
{
	GENERATED_BODY()

public:
	FSInputActionConfig()
	{
		InputAction = nullptr;
	}

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (Categories = "InputTag"))
	FGameplayTag InputTag;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UInputAction* InputAction;

	bool IsValid() const
	{
		return InputTag.IsValid() && InputAction != nullptr;
	}
};

UCLASS()
class SANDBOX_API USInputConfig : public UDataAsset
{
	GENERATED_BODY()
public:
	USInputConfig();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UInputMappingContext* DefaultMappingContext;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(TitleProperty = "InputTag"))
	TArray<FSInputActionConfig> NativeInputActions;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(TitleProperty = "InputTag"))
	TArray<FSInputActionConfig> AbilityInputActions;

	UInputAction* FindNativeInputActionByTag(const FGameplayTag& InInputTag) const;
};
