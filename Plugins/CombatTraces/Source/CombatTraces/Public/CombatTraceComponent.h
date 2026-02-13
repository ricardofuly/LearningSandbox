// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CombatTraceComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FSubstepTraceHitSignature,const FHitResult&,Hit);

UCLASS(ClassGroup=(Combat), meta=(BlueprintSpawnableComponent))
class COMBATTRACES_API UCombatTraceComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UCombatTraceComponent();
	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	UFUNCTION(BlueprintCallable)
	void StartTrace(USceneComponent* InMesh, FName InStartSocket, FName InEndSocket);
	
	UFUNCTION(BlueprintCallable)
	void StopTrace();
	
	UPROPERTY(BlueprintAssignable)
	FSubstepTraceHitSignature OnTraceHit;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	
	void PerformSubstepTrace();

	FVector GetSocketLocation(USceneComponent* Mesh, FName SocketName) const;
	
	UPROPERTY(EditAnywhere, Category="Trace")
	float MaxSubstepDistance = 25.f;

	UPROPERTY(EditAnywhere, Category="Trace")
	TEnumAsByte<ECollisionChannel> TraceChannel = ECC_Pawn;

	UPROPERTY(EditAnywhere, Category="Debug")
	bool bDrawDebug = false;

private:
	bool bTracing = false;

	UPROPERTY()
	USceneComponent* Mesh = nullptr;
	
	FName StartSocket;
	FName EndSocket;

	FVector PrevStart;
	FVector PrevEnd;

	UPROPERTY()
	TSet<AActor*> HitActors;
};
