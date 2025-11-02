// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputComponent.h"
#include "Data/LInputConfig.h"
#include "LEnhancedInputComponent.generated.h"


UCLASS()
class LEARNING_API ULEnhancedInputComponent : public UEnhancedInputComponent
{
	GENERATED_BODY()

public:
 
	template<class UserClass, typename FuncType>
	void BindActionByTag(const ULInputConfig* InputConfig, const FGameplayTag& InputTag, ETriggerEvent TriggerEvent, UserClass* Object, FuncType Func);
};
 
template<class UserClass, typename FuncType>
void ULEnhancedInputComponent::BindActionByTag(const ULInputConfig* InputConfig, const FGameplayTag& InputTag, ETriggerEvent TriggerEvent, UserClass* Object, FuncType Func)
{
	check(InputConfig);
	if (const UInputAction* IA = InputConfig->FindInputActionForTag(InputTag))
	{
		BindAction(IA, TriggerEvent, Object, Func);
	}
};
