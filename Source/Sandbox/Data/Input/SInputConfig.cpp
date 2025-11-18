// Fill out your copyright notice in the Description page of Project Settings.


#include "SInputConfig.h"

USInputConfig::USInputConfig()
{
}

UInputAction* USInputConfig::FindNativeInputActionByTag(const FGameplayTag& InInputTag) const
{
	for (const FSInputActionConfig& InputActionConfig : NativeInputActions)
	{
		if (InputActionConfig.InputTag == InInputTag && InputActionConfig.InputAction)
		{
			return InputActionConfig.InputAction;
		}
	}
	return nullptr;
}
