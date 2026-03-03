// Fill out your copyright notice in the Description page of Project Settings.


#include "FunctionLibrary/DungeonFunctionLibrary.h"

#include "DungeonGeneratorSubsystem.h"

void UDungeonFunctionLibrary::GenerateDungeon(UObject* WorldContextObject, UDungeonGeneratorConfig* Config, const FTransform& StartTransform)
{
	if (UDungeonGeneratorSubsystem* Sub = GetSubsystem(WorldContextObject))
		Sub->GenerateDungeon(Config, StartTransform);
}

void UDungeonFunctionLibrary::UnloadDungeon(UObject* WorldContextObject)
{
	if (UDungeonGeneratorSubsystem* Sub = GetSubsystem(WorldContextObject))
		Sub->UnloadDungeon();
}

bool UDungeonFunctionLibrary::IsDungeonGenerating(UObject* WorldContextObject)
{
	if (UDungeonGeneratorSubsystem* Sub = GetSubsystem(WorldContextObject))
		return Sub->IsGenerating();
	return false;
}

UDungeonGeneratorSubsystem* UDungeonFunctionLibrary::GetSubsystem(UObject* WorldContextObject)
{
	if (!WorldContextObject) return nullptr;
	UWorld* World = WorldContextObject->GetWorld();
	return World ? World->GetSubsystem<UDungeonGeneratorSubsystem>() : nullptr;
}
