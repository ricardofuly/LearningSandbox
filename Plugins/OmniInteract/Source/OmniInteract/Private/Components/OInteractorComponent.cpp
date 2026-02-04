// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/OInteractorComponent.h"

#include "DataAssets/OInteractionRules.h"
#include "Interfaces/OGroupInteractable.h"
#include "Net/UnrealNetwork.h"


struct FInteractionGroupRules;
// Sets default values for this component's properties
UOInteractorComponent::UOInteractorComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	
	SetIsReplicatedByDefault(true);
}


// Called when the game starts
void UOInteractorComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UOInteractorComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                          FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UOInteractorComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	DOREPLIFETIME(UOInteractorComponent, FocusedActor);
}

void UOInteractorComponent::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!OtherActor || !OtherActor->Implements<UOGroupInteractable>()) return;

	OverlappingInteractables.Add(OtherActor);
	GroupedInteractables.FindOrAdd(OtherActor->GetClass()).Actors.Add(OtherActor);
}

void UOInteractorComponent::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	OverlappingInteractables.Remove(OtherActor);

	if (FActorGroup* Group = GroupedInteractables.Find(OtherActor->GetClass()))
	{
		Group->Actors.Remove(OtherActor);
		if (Group->Actors.Num() == 0)
		{
			GroupedInteractables.Remove(OtherActor->GetClass());
		}
	}
}

void UOInteractorComponent::UpdateFocusedInteraction()
{
	// CLIENT-SIDE ONLY
	if (!GetOwner() || !GetOwner()->HasAuthority()) return;
	
	FInteractionContext NewContext;
	
	AActor* OwnerActor = GetOwner();


	FVector ViewLoc;
	FRotator ViewRot;
	OwnerActor->GetActorEyesViewPoint(ViewLoc, ViewRot);


	const FVector TraceStart = ViewLoc;
	const FVector TraceEnd = TraceStart + (ViewRot.Vector() * 500.f);


	FHitResult Hit;
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(OwnerActor);


	bool bHit = GetWorld()->LineTraceSingleByChannel(
	Hit,
	TraceStart,
	TraceEnd,
	ECC_Visibility,
	Params
	);
	
	AActor* NewFocusedActor = nullptr;
	TSubclassOf<AActor> NewFocusedGroupClass = nullptr;


	if (bHit && Hit.GetActor())
	{
		AActor* HitActor = Hit.GetActor();


		if (OverlappingInteractables.Contains(HitActor))
		{
			NewFocusedActor = HitActor;
			NewFocusedGroupClass = HitActor->GetClass();
		}
	}
	
	NewContext.FocusedActor = FocusedActor;
	
	if (!FocusedActor || !FocusedGroupClass)
	{
		OnInteractionContextChanged.Broadcast(NewContext);
		return;
	}
	
	FocusedActor = NewFocusedActor;
	FocusedGroupClass = NewFocusedGroupClass;
	
	// ==============================
	// Build interaction options
	// ==============================


	TArray<FInteractionOption> Options;


	// Build actor list from group
	TArray<AActor*> GroupActors;
	if (const FActorGroup* Group = GroupedInteractables.Find(FocusedGroupClass))
	{
		for (const TWeakObjectPtr<AActor>& WeakActor : Group->Actors)
		{
			if (WeakActor.IsValid())
			{
				GroupActors.Add(WeakActor.Get());
			}
		}
	}
	
	if (GroupActors.Num() == 0)
	{
		OnInteractionContextChanged.Broadcast(NewContext);
		return;
	}
		


	// Apply rules (client-side preview only)
	const FInteractionGroupRules* Rules = InteractionRules
	? InteractionRules->GetRulesForClass(FocusedGroupClass)
	: nullptr;


	if (Rules && GroupActors.Num() > Rules->MaxActorsPerInteraction)
	{
		GroupActors.SetNum(Rules->MaxActorsPerInteraction);
	}
	
	// Group options
	if (FocusedActor->Implements<UOGroupInteractable>())
	{
		IOGroupInteractable::Execute_GetGroupInteractionOptions(
		FocusedActor,
		GroupActors,
		Options
		);
	}
	
	// Individual options
	for (AActor* Actor : GroupActors)
	{
		if (Actor->Implements<UOGroupInteractable>())
		{
			IOGroupInteractable::Execute_GetInteractionData(Actor, NewContext.SingleOptions);
		}
	}
	
	// ==============================
	// Select best option by priority
	// ==============================


	float BestScore = -FLT_MAX;
	
	auto EvaluateOptions =
		[&](const TArray<FInteractionOption>& InteractOptions)
		{
			for (const FInteractionOption& Opt : InteractOptions)
			{
				float Score = Opt.Priority;

				if (Opt.bGroupOption)
				{
					Score += GroupActors.Num() * 0.1f;
				}

				if (Score > BestScore)
				{
					BestScore = Score;
					NewContext.BestOption = Opt;
				}
			}
		};

	EvaluateOptions(NewContext.SingleOptions);

	for (const auto& Pair : NewContext.GroupOptions)
	{
		EvaluateOptions(Pair.Value.Options);
	}
	
	OnInteractionContextChanged.Broadcast(NewContext);
}

void UOInteractorComponent::ServerInteract_Implementation()
{
	if (!FocusedActor || !GroupedInteractables.Contains(FocusedGroupClass))
		return;


	TArray<AActor*> GroupActors;
	if (const FActorGroup* Group = GroupedInteractables.Find(FocusedGroupClass))
	{
		for (const TWeakObjectPtr<AActor>& WeakActor : Group->Actors)
		{
			if (WeakActor.IsValid())
			{
				GroupActors.Add(WeakActor.Get());
			}
		}
	}


	const FInteractionGroupRules* Rules = InteractionRules
	? InteractionRules->GetRulesForClass(FocusedGroupClass)
	: nullptr;


	if (Rules && GroupActors.Num() > Rules->MaxActorsPerInteraction)
	{
		GroupActors.SetNum(Rules->MaxActorsPerInteraction);
	}


	// Group interaction
	if (FocusedActor->Implements<UOGroupInteractable>())
	{
		IOGroupInteractable::Execute_InteractGroup(FocusedActor, GetOwner(), GroupActors, FocusedOptionIndex);
		return;
	}
	
	// Fallback: individual interaction
	IOGroupInteractable::Execute_Interact(FocusedActor, GetOwner(), FocusedOptionIndex);
}

void UOInteractorComponent::OnRep_FocusedActor()
{
	UpdateFocusedInteraction();
}

