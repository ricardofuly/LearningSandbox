// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "Misc/LStructTypes.h"
#include "LAbilitySystemComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class LEARNING_API ULAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	ULAbilitySystemComponent();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
							   FActorComponentTickFunction* ThisTickFunction) override;

	virtual void OnGiveAbility(FGameplayAbilitySpec& AbilitySpec) override;
	virtual void OnRep_ActivateAbilities() override;

	void OnAbilityInputPressed(const FGameplayTag& InInputTag);
	void OnAbilityInputReleased(const FGameplayTag& InInputTag);

	UFUNCTION(BlueprintCallable, Category = "Solaries | Abilities")
	void SetAbilityLevel(TSubclassOf<UGameplayAbility> AbilityClass, int32 NewLevel);

	UFUNCTION(BlueprintCallable, Category = "Solaries | Abilities")
	void AddToAbilityLevel(TSubclassOf<UGameplayAbility> AbilityClass, int32 LevelDelta = 1);

	UFUNCTION(BlueprintCallable, Category = "Solaries | Abilities")
	void GrantPlayerWeaponAbilities(const TArray<FLPlayerAbilitySet>& InDefaultWeaponAbilities, int32 ApplyLevel, TArray<FGameplayAbilitySpecHandle>& OutGrantedAbilitiesHandles);

	UFUNCTION(BlueprintCallable, Category = "Solaries | Abilities")
	void RemoveGrantedAbilities(UPARAM(ref) TArray<FGameplayAbilitySpecHandle>& InSpecHandleToRemove);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	
	
private:
	void HandleAutoActivateAbility(const FGameplayAbilitySpec& AbilitySpec);


};
