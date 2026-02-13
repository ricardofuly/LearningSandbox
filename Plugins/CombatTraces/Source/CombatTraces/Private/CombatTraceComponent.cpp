// Fill out your copyright notice in the Description page of Project Settings.


#include "CombatTraceComponent.h"


// Sets default values for this component's properties
UCombatTraceComponent::UCombatTraceComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.TickGroup = TG_PrePhysics;

	// ...
}


// Called when the game starts
void UCombatTraceComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UCombatTraceComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!bTracing || !Mesh) return;

	PerformSubstepTrace();
}

void UCombatTraceComponent::StartTrace(USceneComponent* InMesh, FName InStartSocket, FName InEndSocket)
{
	Mesh = InMesh;
	StartSocket = InStartSocket;
	EndSocket = InEndSocket;

	PrevStart = GetSocketLocation(Mesh, StartSocket);
	PrevEnd   = GetSocketLocation(Mesh, EndSocket);

	HitActors.Reset();
	bTracing = true;
}

void UCombatTraceComponent::StopTrace()
{
	bTracing = false;
	Mesh = nullptr;
	HitActors.Reset();
}

void UCombatTraceComponent::PerformSubstepTrace()
{
	FVector CurrStart = GetSocketLocation(Mesh, StartSocket);
	FVector CurrEnd   = GetSocketLocation(Mesh, EndSocket);

	float Distance = FVector::Distance(PrevStart, CurrStart);
	int32 Steps = FMath::CeilToInt(Distance / MaxSubstepDistance);
	Steps = FMath::Max(1, Steps);

	for (int32 i = 0; i < Steps; i++)
	{
		float T0 = (float)i / Steps;
		float T1 = (float)(i + 1) / Steps;

		FVector StepStartA = FMath::Lerp(PrevStart, CurrStart, T0);
		FVector StepEndA   = FMath::Lerp(PrevEnd,   CurrEnd,   T0);

		FVector StepStartB = FMath::Lerp(PrevStart, CurrStart, T1);
		FVector StepEndB   = FMath::Lerp(PrevEnd,   CurrEnd,   T1);

		FHitResult Hit;

		bool bHit = GetWorld()->LineTraceSingleByChannel(
			Hit,
			StepStartA,
			StepEndB,
			TraceChannel
		);

		if (bDrawDebug)
		{
			DrawDebugLine(
				GetWorld(),
				StepStartA,
				StepEndB,
				bHit ? FColor::Red : FColor::Green,
				false,
				1.0f,
				0,
				1.5f
			);
		}

		if (bHit && Hit.GetActor() && !HitActors.Contains(Hit.GetActor()))
		{
			HitActors.Add(Hit.GetActor());
			OnTraceHit.Broadcast(Hit);
			break;
		}
	}

	PrevStart = CurrStart;
	PrevEnd   = CurrEnd;
}

FVector UCombatTraceComponent::GetSocketLocation(USceneComponent* InMesh, FName SocketName) const
{
	if (!InMesh) return FVector::ZeroVector;

	if (const USkeletalMeshComponent* SkelMesh = Cast<USkeletalMeshComponent>(InMesh))
	{
		return SkelMesh->GetSocketLocation(SocketName);
	}

	return InMesh->GetComponentLocation();
}

