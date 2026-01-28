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
	StackAttributeSet = CreateDefaultSubobject<USStackAttributeSet>("StackAttributeSet");
	
	SetNetUpdateFrequency(100.f);
}

TArray<TObjectPtr<USAttributeSetBase>> ASPlayerState::GetAttributeSet() const
{
	TArray<TObjectPtr<USAttributeSetBase>> AttributeSets;
	AttributeSets.Add(MetaAttributeSet);
	AttributeSets.Add(PrimaryAttributeSet);
	AttributeSets.Add(SecondaryAttributeSet);
	AttributeSets.Add(StackAttributeSet);
	
	return AttributeSets;
}

void ASPlayerState::BeginPlay()
{
	Super::BeginPlay();
	
	RequestCharacterDataToLoad(PlayerInitialData);
	InitActorInfo(this, GetPawn());

	for (USAttributeSetBase* AttributeSet : GetAttributeSet())
	{
		AbilitySystemComponent->AddAttributeSetSubobject(AttributeSet);
	}
}

void ASPlayerState::RequestCharacterDataToLoad(TSoftObjectPtr<USPlayerInitialData> InCharacterData)
{
	if (!InCharacterData.IsNull())
	{
		FStreamableManager& StreamableManager = UAssetManager::GetStreamableManager();
		
		FSoftObjectPath SoftObjectPath = PlayerInitialData.ToSoftObjectPath();
		StreamableHandle = StreamableManager.RequestAsyncLoad(SoftObjectPath, FStreamableDelegate::CreateUObject(this, &ThisClass::ApplyStartUpData, InCharacterData));
	}
}

void ASPlayerState::ApplyStartUpData(TSoftObjectPtr<USPlayerInitialData> InCharacterData)
{
	if (!HasAuthority()) return;
	if (PlayerInitialData.IsValid())
	{
		if (const USPlayerInitialData* LoadData = InCharacterData.Get())
		{
			LoadData->GiveToAbilitySystemComponent(AbilitySystemComponent);
		}
	}
	StreamableHandle.Reset();
}

void ASPlayerState::InitActorInfo(APlayerState* PlayerState, APawn* InPawn)
{
	AbilitySystemComponent->InitAbilityActorInfo(PlayerState, InPawn);
}
