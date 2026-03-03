// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DungeonDoor.generated.h"

class UDungeonGeneratorConfig;

UCLASS()
class DUNGEONGENERATOR_API ADungeonDoor : public AActor
{
	GENERATED_BODY()
	
public:	
	ADungeonDoor();

protected:
	virtual void BeginPlay() override;

public:	
	/** Transform where the dungeon should start (Local origin of Room 0) */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Dungeon")
	TObjectPtr<USceneComponent> ExitPoint;

	UPROPERTY(EditAnywhere, Category = "Dungeon")
	TObjectPtr<UDungeonGeneratorConfig> Config;

	/** Starts the procedural generation process. */
	UFUNCTION(BlueprintCallable, Category = "Dungeon")
	void StartDungeonGeneration();

	/** Called when the dungeon is fully generated and rooms are loaded. */
	UFUNCTION()
	void OnDungeonComplete(bool bSuccess);

	/** Visual event to open the door mesh. Implement in BP. */
	UFUNCTION(BlueprintImplementableEvent, Category = "Dungeon")
	void OpenDoor();

    /** Visual event if generation fails. */
	UFUNCTION(BlueprintImplementableEvent, Category = "Dungeon")
	void OnGenerationFailed();
};
