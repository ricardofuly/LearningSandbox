// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/LPlayerState.h"

ALPlayerState::ALPlayerState()
{
	AbilitySystemComponent = CreateDefaultSubobject<ULAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(ReplicationMode);
}

void ALPlayerState::OnPossess(APawn* InPawn)
{
	if (IsValid(AbilitySystemComponent) && IsValid(InPawn))
	{
		AbilitySystemComponent->InitAbilityActorInfo(this, InPawn);
	}
}

void ALPlayerState::OnRep_PlayerState()
{
	if (IsValid(AbilitySystemComponent) && IsValid(GetPawn()))
	{
		AbilitySystemComponent->InitAbilityActorInfo(this, GetPawn());
	}
}

void ALPlayerState::BeginPlay()
{
	Super::BeginPlay();
}
