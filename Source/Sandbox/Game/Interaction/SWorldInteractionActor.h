// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/SInteractionInterface.h"
#include "SWorldInteractionActor.generated.h"

UCLASS()
class SANDBOX_API ASWorldInteractionActor : public AActor, public ISInteractionInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ASWorldInteractionActor();
	
	virtual const USInteractionDefinition* GetInteractionDefinition() const override;
	virtual FVector GetInteractionLocation() const override;
	
	UFUNCTION(BlueprintNativeEvent, Category = Interaction)
	void Interact();
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	USInteractionDefinition* InteractionDefinition;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
