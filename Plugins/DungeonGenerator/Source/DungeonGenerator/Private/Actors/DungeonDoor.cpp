// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/DungeonDoor.h"
#include "DungeonGeneratorSubsystem.h"
#include "Data/DungeonGeneratorConfig.h"

ADungeonDoor::ADungeonDoor()
{
	PrimaryActorTick.bCanEverTick = false;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceneRoot"));
	
	ExitPoint = CreateDefaultSubobject<USceneComponent>(TEXT("ExitPoint"));
	ExitPoint->SetupAttachment(RootComponent);
}

void ADungeonDoor::BeginPlay()
{
	Super::BeginPlay();
}

void ADungeonDoor::StartDungeonGeneration()
{
	if (!Config)
	{
		UE_LOG(LogTemp, Warning, TEXT("DungeonDoor: No config assigned!"));
		return;
	}

	UWorld* World = GetWorld();
	if (!World) return;

	UDungeonGeneratorSubsystem* Subsystem = World->GetSubsystem<UDungeonGeneratorSubsystem>();
	if (Subsystem)
	{
		// Bind to the completion delegate
		Subsystem->OnDungeonGenerated.AddDynamic(this, &ADungeonDoor::OnDungeonComplete);
		
		// Start generation relative to the ExitPoint transform
		Subsystem->GenerateDungeon(Config, ExitPoint->GetComponentTransform());
	}
}

void ADungeonDoor::OnDungeonComplete(bool bSuccess)
{
	if (bSuccess)
	{
		OpenDoor();
	}
	else
	{
		OnGenerationFailed();
	}

	// Unbind to prevent multiple calls if generated again
	if (UWorld* World = GetWorld())
	{
		if (UDungeonGeneratorSubsystem* Subsystem = World->GetSubsystem<UDungeonGeneratorSubsystem>())
		{
			Subsystem->OnDungeonGenerated.RemoveDynamic(this, &ADungeonDoor::OnDungeonComplete);
		}
	}
}
