#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "GameplayEffect.h"
#include "GameplayTagContainer.h"

/**
 * Helper functions to create and apply GameplayEffects with SetByCaller magnitudes.
 */
namespace SandboxGEs
{
	bool ApplySetByCallerToASC(UAbilitySystemComponent* TargetASC,
		const TSubclassOf<UGameplayEffect> GEClass,
		const FGameplayTag& SetByCallerTag,
		const float Magnitude,
		AActor* Instigator = nullptr,
		FActiveGameplayEffectHandle* OutHandle = nullptr);
}
