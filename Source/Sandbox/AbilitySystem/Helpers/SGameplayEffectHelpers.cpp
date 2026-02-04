#include "SGameplayEffectHelpers.h"
#include "AbilitySystemComponent.h"
#include "GameplayEffect.h"
#include "GameplayEffectTypes.h"
#include "GameplayTagContainer.h"
#include "GameFramework/Actor.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/Controller.h"

namespace SandboxGEs
{
	bool ApplySetByCallerToASC(UAbilitySystemComponent* TargetASC,
		const TSubclassOf<UGameplayEffect> GEClass,
		const FGameplayTag& SetByCallerTag,
		const float Magnitude,
		AActor* Instigator,
		FActiveGameplayEffectHandle* OutHandle)
	{
		if (!TargetASC)
		{
			UE_LOG(LogTemp, Warning, TEXT("ApplySetByCallerToASC: TargetASC is null."));
			return false;
		}

		if (!GEClass)
		{
			UE_LOG(LogTemp, Warning, TEXT("ApplySetByCallerToASC: GEClass is null."));
			return false;
		}

		if (FMath::IsNearlyZero(Magnitude))
		{
			UE_LOG(LogTemp, Warning, TEXT("ApplySetByCallerToASC: Magnitude is zero, nothing to apply."));
			return false;
		}

		// Ensure we run on the server / authority
		if (AActor* OwnerActor = Cast<AActor>(TargetASC->GetOwner()))
		{
			if (!OwnerActor->HasAuthority())
			{
				UE_LOG(LogTemp, Warning, TEXT("ApplySetByCallerToASC: Owner does not have authority. Call this on the server."));
				return false;
			}
		}

		FGameplayEffectContextHandle ContextHandle = TargetASC->MakeEffectContext();
		if (Instigator)
		{
			AController* Controller = Instigator->GetInstigatorController();
			if (APawn* Pawn = Cast<APawn>(Instigator))
			{
				Controller = Pawn->GetController();
			}

			ContextHandle.AddInstigator(Instigator, Controller);
			ContextHandle.AddSourceObject(Instigator);
		}

		FGameplayEffectSpecHandle SpecHandle = TargetASC->MakeOutgoingSpec(GEClass, 1.0f, ContextHandle);
		if (!SpecHandle.IsValid())
		{
			UE_LOG(LogTemp, Warning, TEXT("ApplySetByCallerToASC: Failed to create SpecHandle."));
			return false;
		}

		SpecHandle.Data.Get()->SetSetByCallerMagnitude(SetByCallerTag, Magnitude);

		FActiveGameplayEffectHandle ActiveHandle = TargetASC->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
		if (OutHandle)
		{
			*OutHandle = ActiveHandle;
		}

		return ActiveHandle.IsValid();
	}

}
