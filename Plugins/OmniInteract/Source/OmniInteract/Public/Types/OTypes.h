#pragma once

#include "CoreMinimal.h"
#include "OTypes.generated.h"

USTRUCT()
struct FActorGroup
{
	GENERATED_BODY()

	UPROPERTY()
	TArray<TWeakObjectPtr<AActor>> Actors;
};

USTRUCT(BlueprintType)
struct FInteractionOption
{
	GENERATED_BODY()


	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText DisplayText;


	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float Priority = 0.f;


	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool bHoldInteraction = false;


	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float HoldTime = 0.f;


	// True if this option affects the whole group
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool bGroupOption = false;
};

USTRUCT(BlueprintType)
struct FInteractionOptionGroup
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly)
	TArray<FInteractionOption> Options;
};

USTRUCT(BlueprintType)
struct FInteractionGroupRules
{
	GENERATED_BODY()


	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> ActorClass;


	UPROPERTY(EditAnywhere)
	bool bAllowGroupInteraction = true;


	UPROPERTY(EditAnywhere)
	int32 MaxActorsPerInteraction = 10;


	UPROPERTY(EditAnywhere)
	float MaxDistance = 250.f;
};

USTRUCT(BlueprintType)
struct FInteractionContext
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly)
	AActor* FocusedActor = nullptr;

	// Todas as opções individuais (atores)
	UPROPERTY(BlueprintReadOnly)
	TArray<FInteractionOption> SingleOptions;

	// Todas as opções por grupo (classe)
	UPROPERTY(BlueprintReadOnly)
	TMap<TSubclassOf<AActor>, FInteractionOptionGroup> GroupOptions;

	// Opção automaticamente selecionada (highlight)
	UPROPERTY(BlueprintReadOnly)
	FInteractionOption BestOption;

	bool IsValid() const
	{
		return FocusedActor != nullptr &&
			   (SingleOptions.Num() > 0 || GroupOptions.Num() > 0);
	}
};