// Fill out your copyright notice in the Description page of Project Settings.


#include "DungeonGeneratorSubsystem.h"

#include "DungeonStreamingManager.h"
#include "Data/DungeonGeneratorConfig.h"
#include "Tasks/DungeonGenerationTask.h"

void UDungeonGeneratorSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
}

void UDungeonGeneratorSubsystem::Deinitialize()
{
	UnloadDungeon();
	Super::Deinitialize();
}

void UDungeonGeneratorSubsystem::GenerateDungeonDefault(UDungeonGeneratorConfig* Config)
{
	if (Config)
	{
		GenerateDungeon(Config, FTransform(Config->DungeonOrigin));
	}
}

void UDungeonGeneratorSubsystem::GenerateDungeon(UDungeonGeneratorConfig* Config, const FTransform& StartTransform)
{
	if (!Config)
	{
		UE_LOG(LogTemp, Warning, TEXT("DungeonGenerator: Config is null."));
		OnDungeonGenerated.Broadcast(false);
		return;
	}
	if (bIsGenerating)
	{
		UE_LOG(LogTemp, Warning, TEXT("DungeonGenerator: Already in progress."));
		return;
	}
	UnloadDungeon();
	bIsGenerating = true;
	ActiveConfig  = Config;
	ActiveStartTransform = StartTransform;
	
	FDungeonGenerationTask* Task = new FDungeonGenerationTask(Config, StartTransform);
	
	// WeakPtr para capturar o subsystem com segurança (evita raw 'this' em lambda)
	TWeakObjectPtr<UDungeonGeneratorSubsystem> WeakThis(this);
	Async(EAsyncExecution::ThreadPool, [Task, WeakThis]()
	{
		// Roda o algoritmo na thread pool (sem travar o game thread)
		FDungeonLayout Layout = Task->RunGeneration();
		delete Task;
		// Retorna para o game thread via AsyncTask
		AsyncTask(ENamedThreads::GameThread,
			[WeakThis, Layout = MoveTemp(Layout)]() mutable
			{
				// WeakPtr garante que o subsystem ainda existe
				if (UDungeonGeneratorSubsystem* Sub = WeakThis.Get())
				{
					Sub->OnGenerationComplete(MoveTemp(Layout));
				}
			});
	});
}

void UDungeonGeneratorSubsystem::UnloadDungeon()
{
	if (StreamingManager)
	{
		StreamingManager->UnloadAll();
		StreamingManager->Destroy();
		StreamingManager = nullptr;
	}
	ActiveConfig = nullptr;
}

void UDungeonGeneratorSubsystem::NotifyAllRoomsLoaded(bool bSuccess)
{
	OnDungeonGenerated.Broadcast(bSuccess);
}

void UDungeonGeneratorSubsystem::OnGenerationComplete(FDungeonLayout Layout)
{
	bIsGenerating = false;
	if (!Layout.bSuccess)
	{
		UE_LOG(LogTemp, Error, TEXT("DungeonGenerator: %s"), *Layout.ErrorMessage);
		OnDungeonGenerated.Broadcast(false);
		return;
	}
	UWorld* World = GetWorld();
	if (!World) { OnDungeonGenerated.Broadcast(false); return; }
	// Spawn the streaming manager in the persistent level
	FActorSpawnParameters Params;
	Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	StreamingManager = World->SpawnActor<ADungeonStreamingManager>(
		ADungeonStreamingManager::StaticClass(), FTransform::Identity, Params);
	if (StreamingManager)
	{
		StreamingManager->SetOwnerSubsystem(this);
		StreamingManager->SetBaseTransform(ActiveStartTransform);
		StreamingManager->LoadDungeonLayout(Layout, ActiveConfig);
	}
	else
	{
		OnDungeonGenerated.Broadcast(false);
	}
}

void UDungeonGeneratorSubsystem::NotifyRoomLoaded(int32 RoomIndex, ADungeonRoomActor* RoomActor)
{
	OnRoomLoaded.Broadcast(RoomIndex, RoomActor);
}
