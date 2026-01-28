// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/RZoneActor.h"
#include "Engine/PawnIterator.h"
#include "AbilitySystemGlobals.h"
#include "Net/UnrealNetwork.h"


// Sets default values
ARZoneActor::ARZoneActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	bReplicates = true;

	ZoneMesh = CreateDefaultSubobject<UStaticMeshComponent>("ZoneMesh");
	SetRootComponent(ZoneMesh);

	CurrentStageIndex = 0;

	ZoneMesh->SetWorldScale3D(FVector(CurrentRadius, CurrentRadius, Height));
}

// Called when the game starts or when spawned
void ARZoneActor::BeginPlay()
{
	Super::BeginPlay();
	
	CurrentRadius = Radius;
	SetReplicateMovement(true);

	if (HasAuthority())
	{
		GetWorldTimerManager().SetTimer(DamageTimerHandle, this, &ThisClass::ApplyZoneDamage, 1.f, true);
		StartNextStage();
	}
	
}

// Called every frame
void ARZoneActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (HasAuthority() && bIsShrinking)
	{
		float Alpha = (GetWorld()->GetTimeSeconds() - ShrinkStartTime) / ShrinkDuration;
		CurrentRadius = FMath::Lerp(StartRadius, TargetRadius, Alpha);
		CurrentRadius = FMath::Max(CurrentRadius, MinZoneRadius);

		ZoneMesh->SetWorldScale3D(FVector(CurrentRadius / BaseMeshRadius, CurrentRadius / BaseMeshRadius, Height));

		if (bShowDebug)
		{
			DrawDebugSphere(GetWorld(), GetActorLocation(), CurrentRadius, 32, FColor::Red, false, -1, 0, 10.f);
		}


		if (Alpha >= 1.f)
		{
			FinishShrink();
		}
	}
}

void ARZoneActor::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	DOREPLIFETIME(ThisClass, CurrentRadius);
}

float ARZoneActor::GetTimeUntilNextShrink() const
{
	if (HasAuthority())
	{
		float Remaining = NextShrinkStartTime - GetWorld()->GetTimeSeconds();
		return FMath::Max(Remaining, 0.0f);
	}
	return 0.0f;
}

void ARZoneActor::StartNextStage()
{
	if (CurrentStageIndex >= ZoneStages.Num()) return;

	const FZoneStageData& StageData = ZoneStages[CurrentStageIndex];

	NextShrinkStartTime = GetWorld()->GetTimeSeconds() + StageData.WaitTimeBeforeShrink;
	TimeUntilNextShrink = StageData.WaitTimeBeforeShrink;

	GetWorldTimerManager().SetTimer(StageTimerHandle, this, &ThisClass::BeginShrink, StageData.WaitTimeBeforeShrink, false);
}

void ARZoneActor::BeginShrink()
{
	if (CurrentStageIndex >= ZoneStages.Num()) return;

	const FZoneStageData& StageData = ZoneStages[CurrentStageIndex];
	StartRadius = CurrentRadius;
	TargetRadius = FMath::Max(StageData.TargetRadius, MinZoneRadius);
	ShrinkDuration = StageData.ShrinkDuration;
	ShrinkStartTime = GetWorld()->GetTimeSeconds();

	bIsShrinking = true;

	OnZoneShrinkStarted.Broadcast(CurrentStageIndex);
}

void ARZoneActor::FinishShrink()
{
	bIsShrinking = false;
	CurrentRadius = TargetRadius;
	ZoneMesh->SetWorldScale3D(FVector(CurrentRadius, CurrentRadius, Height));

	UpdateVisualMesh();

	CurrentStageIndex++;

	if (bShowDebug)
	{
		DrawDebugSphere(GetWorld(), GetActorLocation(), CurrentRadius, 32, FColor::Red, true, -1, 0, 10.f);
	}

	if (CurrentStageIndex <= ZoneStages.Num())
	{
		StartNextStage();
	}
}

void ARZoneActor::ApplyZoneDamage()
{
	if (!HasAuthority()) return;

	FVector ZoneCenter = GetActorLocation();

	for (TActorIterator<APawn> Iterator(GetWorld()); Iterator; ++Iterator)
	{
		APawn* Pawn = *Iterator;
		if (!Pawn) continue;

		float Distance = FVector::Dist2D(ZoneCenter, Pawn->GetActorLocation());
		bool bIsInside = Distance <= CurrentRadius;

		if (bShowDebug)
		{
			GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Green, FString::Printf(TEXT("Pawn: %s, Distance: %.2f, Inside: %s, Current Radius: %.2f"), *Pawn->GetName(), Distance, bIsInside ? TEXT("Yes") : TEXT("No"), CurrentRadius));
		}

		UAbilitySystemComponent* ASC = UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(Pawn);

		if (!bIsInside)
		{
			if (ASC && ZoneDamageEffectClass)
			{
				FGameplayEffectContextHandle ContextHandle = ASC->MakeEffectContext();
				ContextHandle.AddSourceObject(this);

				FGameplayEffectSpecHandle SpecHandle = ASC->MakeOutgoingSpec(ZoneDamageEffectClass, DamageLevelOutside, ContextHandle);
				if (SpecHandle.IsValid())
				{
					FActiveGameplayEffectHandle ActiveGameplayEffectHandle =  ASC->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
					ActiveDamageEffectsMap.Add(ASC, ActiveGameplayEffectHandle);
				}
			}
		}
		else if (ASC)
		{
			FActiveGameplayEffectHandle FoundGameplayEffectHandle = ActiveDamageEffectsMap.FindRef(ASC);
			if (FoundGameplayEffectHandle.IsValid())
			{
				ASC->RemoveActiveGameplayEffect(FoundGameplayEffectHandle);
				ActiveDamageEffectsMap.Remove(ASC);
			}
		}
	}
}

void ARZoneActor::UpdateVisualMesh()
{
	if (ZoneMesh)
	{
		float Scale = CurrentRadius / BaseMeshRadius;
		ZoneMesh->SetWorldScale3D(FVector(Scale, Scale, Height));
	}
}

void ARZoneActor::OnRep_ZoneRadius()
{
	ZoneMesh->SetWorldScale3D(FVector(CurrentRadius, CurrentRadius, Height));
	UpdateVisualMesh();
}

