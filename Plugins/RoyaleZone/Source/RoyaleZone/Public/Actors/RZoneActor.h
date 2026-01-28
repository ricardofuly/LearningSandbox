// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "GameFramework/Actor.h"
#include "RZoneActor.generated.h"

class UGameplayEffect;
struct FActiveGameplayEffectHandle;
class UAbilitySystemComponent;

USTRUCT(BlueprintType)
struct FZoneStageData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float TargetRadius = 5000.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float WaitTimeBeforeShrink = 10.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ShrinkDuration = 10.f;
};


class UCurveFloat;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnZoneShrinkStarted, int32, StageIndex);

UCLASS()
class ROYALEZONE_API ARZoneActor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ARZoneActor();
	
	virtual void Tick(float DeltaTime) override;
	
	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;

	UPROPERTY(BlueprintAssignable, Category="Royale Zone|Events")
	FOnZoneShrinkStarted OnZoneShrinkStarted;

	UFUNCTION(BlueprintCallable, Category="Royale Zone|Info")
	float GetTimeUntilNextShrink() const;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly ,Category= "Royale Zone")
	UStaticMeshComponent* ZoneMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Royale Zone", meta=(ExposeOnSpawn = true))
	TArray<FZoneStageData> ZoneStages;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Royale Zone")
	float BaseMeshRadius = 100.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Royale Zone" , meta=(ExposeOnSpawn = true))
	float Radius;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Royale Zone", meta=(ExposeOnSpawn = true))
	float Height = 1000.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Royale Zone", meta=(ExposeOnSpawn = true))
	float MinZoneRadius = 200.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Royale Zone", meta=(ExposeOnSpawn = true))
	float DamageLevelOutside = 1.f;

	float TimeUntilNextShrink;
	float NextShrinkStartTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Royale Zone")
	TSubclassOf<UGameplayEffect> ZoneDamageEffectClass;

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing= OnRep_ZoneRadius)
	float CurrentRadius;

	float StartRadius;
	float TargetRadius;
	float ShrinkStartTime;
	float ShrinkDuration;

	int32 CurrentStageIndex;
	bool bIsShrinking;
	
	FTimerHandle StageTimerHandle;
	FTimerHandle DamageTimerHandle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Royale Zone|Debug")
	bool bShowDebug = false;

	void StartNextStage();
	void BeginShrink();
	void FinishShrink();
	void ApplyZoneDamage();

	void UpdateVisualMesh();

	UFUNCTION()
	void OnRep_ZoneRadius();
	
private:

	UPROPERTY()
	TMap<UAbilitySystemComponent*, FActiveGameplayEffectHandle> ActiveDamageEffectsMap;
};
