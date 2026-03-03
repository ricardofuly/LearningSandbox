// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "DungeonFunctionLibrary.generated.h"

class UDungeonGeneratorSubsystem;
class UDungeonGeneratorConfig;
/**
 * 
 */
UCLASS()
class DUNGEONGENERATOR_API UDungeonFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "Dungeon",meta = (WorldContext = "WorldContextObject", DisplayName = "Generate Dungeon"))
	static void GenerateDungeon(UObject* WorldContextObject, UDungeonGeneratorConfig* Config, const FTransform& StartTransform);
	
	UFUNCTION(BlueprintCallable, Category = "Dungeon",meta = (WorldContext = "WorldContextObject", DisplayName = "Unload Dungeon"))
	static void UnloadDungeon(UObject* WorldContextObject);
	
	UFUNCTION(BlueprintPure, Category = "Dungeon",meta = (WorldContext = "WorldContextObject", DisplayName = "Is Dungeon Generating"))
	static bool IsDungeonGenerating(UObject* WorldContextObject);
private:
	static UDungeonGeneratorSubsystem* GetSubsystem(UObject* WorldContextObject);
};
