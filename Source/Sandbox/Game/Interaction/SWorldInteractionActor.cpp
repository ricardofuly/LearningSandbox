// Fill out your copyright notice in the Description page of Project Settings.


#include "SWorldInteractionActor.h"


// Sets default values
ASWorldInteractionActor::ASWorldInteractionActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

const USInteractionDefinition* ASWorldInteractionActor::GetInteractionDefinition() const
{
	return InteractionDefinition;
}

FVector ASWorldInteractionActor::GetInteractionLocation() const
{
	return GetActorLocation();
}

void ASWorldInteractionActor::Interact_Implementation()
{
}

// Called when the game starts or when spawned
void ASWorldInteractionActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASWorldInteractionActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

