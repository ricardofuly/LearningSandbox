// Fill out your copyright notice in the Description page of Project Settings.


#include "SChargeAttributeSet.h"

#include "GameplayEffectExtension.h"
#include "AbilitySystem/Helpers/SGameplayEffectHelpers.h"
#include "Net/UnrealNetwork.h"

USChargeAttributeSet::USChargeAttributeSet()
{
	InitFireBallCharge(0.f);
	InitMaxFireBallCharge(100.f);
}

void USChargeAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	DOREPLIFETIME(ThisClass, FireBallCharge);
	DOREPLIFETIME(ThisClass, MaxFireBallCharge);
}

void USChargeAttributeSet::PreAttributeBaseChange(const FGameplayAttribute& Attribute, float& NewValue) const
{
	Super::PreAttributeBaseChange(Attribute, NewValue);
	
	if (Attribute == GetMaxFireBallChargeAttribute())
	{
		float CurrentCharge = GetFireBallCharge();
		if (CurrentCharge > NewValue)
		{
			NewValue = CurrentCharge;
		}
	}
}

void USChargeAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	if (Data.EvaluatedData.Attribute == GetFireBallChargeAttribute())
	{
		SetFireBallCharge(FMath::Clamp(GetFireBallCharge(), 0.f, GetMaxFireBallCharge()));

		if (GetFireBallCharge() >= GetMaxFireBallCharge())
		{
			SandboxGEs::ApplySetByCallerToASC(
				&Data.Target, 
				TSubclassOf<UGameplayEffect>(StaticClass()->GetDefaultObject<USChargeAttributeSet>()->GetClass()),
				FGameplayTag::RequestGameplayTag(FName("Shared_Event_FireBall_Charged")),
				1.0f,
				Cast<AActor>(Data.Target.GetOwnerActor()));
			SetFireBallCharge(0.f);
		}
	}
	
}
