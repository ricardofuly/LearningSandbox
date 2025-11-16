// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/LInputConfig.h"


UInputAction* ULInputConfig::FindNativeInputActionByTag(const FGameplayTag& InInputTag) const
{
	for (const FTaggedInputAction& InputActionConfig : NativeInputActions)
	{
		if (InputActionConfig.InputTag == InInputTag && InputActionConfig.InputAction)
		{
			return InputActionConfig.InputAction;
		}
	}
	return nullptr;
}
