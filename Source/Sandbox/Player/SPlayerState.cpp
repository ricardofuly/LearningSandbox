// Fill out your copyright notice in the Description page of Project Settings.


#include "SPlayerState.h"

#include "Engine/AssetManager.h"

ASPlayerState::ASPlayerState()
{
	AbilitySystemComponent = CreateDefaultSubobject<USAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(ReplicationMode);

	MetaAttributeSet = CreateDefaultSubobject<USMetaAttributeSet>("MetaAttributeSet");
	PrimaryAttributeSet = CreateDefaultSubobject<USPrimaryAttributeSet>("PrimaryAttributeSet");
	SecondaryAttributeSet = CreateDefaultSubobject<USSecondaryAttributeSet>("SecondaryAttributeSet");
	
	SetNetUpdateFrequency(100.f);
}

void ASPlayerState::OnPossess(APawn* InPawn)
{
	if (IsValid(AbilitySystemComponent) && IsValid(InPawn))
	{
		InitActorInfo(this, InPawn);
	}
	
	if (HasAuthority())
	{
		RequestCharacterDataToLoad(PlayerInitialData);
	}
}

void ASPlayerState::OnRep_PlayerState()
{
	if (IsValid(AbilitySystemComponent) && IsValid(GetPawn()))
	{
		InitActorInfo(this, GetPawn());
	}
	
	RequestCharacterDataToLoad(PlayerInitialData);
}

USAbilitySystemComponent* ASPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

TArray<TObjectPtr<USAttributeSetBase>> ASPlayerState::GetAttributeSet() const
{
	TArray<TObjectPtr<USAttributeSetBase>> AttributeSets;
	AttributeSets.Add(MetaAttributeSet);
	AttributeSets.Add(PrimaryAttributeSet);
	AttributeSets.Add(SecondaryAttributeSet);
	
	return AttributeSets;
}

void ASPlayerState::BeginPlay()
{
	Super::BeginPlay();
	
	RequestCharacterDataToLoad(PlayerInitialData);
	InitActorInfo(this, GetPawn());
}

void ASPlayerState::RequestCharacterDataToLoad(TSoftObjectPtr<USPlayerInitialData> InCharacterData)
{
	if (!InCharacterData.IsNull())
	{
		FStreamableManager& StreamableManager = UAssetManager::GetStreamableManager();
		
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "Loading Player Data...");
		}

		FSoftObjectPath SoftObjectPath = PlayerInitialData.ToSoftObjectPath();
		StreamableHandle = StreamableManager.RequestAsyncLoad(SoftObjectPath, FStreamableDelegate::CreateUObject(this, &ThisClass::ApplyStartUpData, InCharacterData));
	}
}

void ASPlayerState::ApplyStartUpData(TSoftObjectPtr<USPlayerInitialData> InCharacterData)
{
	if (!HasAuthority()) return;
	if (!GetAbilitySystemComponent()) return;
	if (PlayerInitialData.IsValid())
	{
		if (const USPlayerInitialData* LoadData = InCharacterData.Get())
		{
			LoadData->GiveToAbilitySystemComponent(AbilitySystemComponent);
			if (GEngine)
			{
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, "Player Data Applied!");
			}
		}
	}
	StreamableHandle.Reset();
}

void ASPlayerState::InitActorInfo(APlayerState* PlayerState, APawn* InPawn)
{
	AbilitySystemComponent->InitAbilityActorInfo(PlayerState, InPawn);
}
