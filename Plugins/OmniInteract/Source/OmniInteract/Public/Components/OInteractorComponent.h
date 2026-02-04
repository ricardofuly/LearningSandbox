// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Types/OTypes.h"
#include "OInteractorComponent.generated.h"


class UOInteractionRules;
class USphereComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnInteractionContextChanged, const FInteractionContext&, Context);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class OMNIINTERACT_API UOInteractorComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UOInteractorComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;	
	
	// Detection sphere
	UPROPERTY(VisibleAnywhere)
	USphereComponent* InteractionSphere;


	// Individual interactables inside the sphere
	UPROPERTY()
	TSet<TWeakObjectPtr<AActor>> OverlappingInteractables;


	// Grouped interactables by class
	UPROPERTY()
	TMap<TSubclassOf<AActor>, FActorGroup> GroupedInteractables;


	// Gameplay rules
	UPROPERTY(EditDefaultsOnly, Category="Interaction")
	UOInteractionRules* InteractionRules;


	// Current focus
	UPROPERTY(ReplicatedUsing=OnRep_FocusedActor)
	AActor* FocusedActor;


	UPROPERTY()
	TSubclassOf<AActor> FocusedGroupClass;


	UPROPERTY()
	int32 FocusedOptionIndex;
	
	UPROPERTY(BlueprintAssignable, Category="Interaction")
	FOnInteractionContextChanged OnInteractionContextChanged;


	// =====================
	// Overlap callbacks
	// =====================
	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);


	UFUNCTION()
	void OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);


	// Update focus & options (CLIENT ONLY)
	void UpdateFocusedInteraction();


	// Execute interaction (SERVER)
	UFUNCTION(Server, Reliable)
	void ServerInteract();


	UFUNCTION()
	void OnRep_FocusedActor();	
};
