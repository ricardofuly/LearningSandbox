// Fill out your copyright notice in the Description page of Project Settings.


#include "Tags/LGameplayTags.h"

#include "GameplayTagsManager.h"

FGameplayTags FGameplayTags::GameplayTags;

void FGameplayTags::InitializeNativeTags()
{
	UGameplayTagsManager& GameplayTagsManager = UGameplayTagsManager::Get();
 
	GameplayTags.AddAllTags(GameplayTagsManager);
 
	GameplayTagsManager.DoneAddingNativeTags();
}

void FGameplayTags::AddAllTags(UGameplayTagsManager& Manager)
{
	// Inputs
	AddTag(InputTag_Move, "InputTag.Move", "Move input.");
	AddTag(InputTag_Look_Mouse, "InputTag.Look.Mouse", "Look (mouse) input.");
	AddTag(InputTag_Look_Stick, "InputTag.Look.Stick", "Look (stick) input.");
	AddTag(InputTag_Jump, "InputTag.Jump", "Jump input");
	AddTag(InputTag_Attack, "InputTag.Attack", "Attack input.");
	AddTag(InputTag_Toggleable, "InputTag.Toggleable", "Toggleable input.");
	AddTag(InputTag_MustBeHeld, "InputTag.MustBeHeld", "Must Be Held input.");
	AddTag(Shared_Ability_OnGiven, "Shared.Ability.OnGiven", "Activate Ability on Given.");
	
	// Events
	AddTag(Events_Death, "Events.Death", "Notify Entity Death State.");
	AddTag(Events_Panting, "Events.Panting", "Notify Entity is Out of Stamina.");
	AddTag(Events_LevelUp, "Events.LevelUp", "Notify Entity is Leveled Up.");
}

void FGameplayTags::AddTag(FGameplayTag& OutTag, const ANSICHAR* TagName, const ANSICHAR* TagComment)
{
	OutTag = UGameplayTagsManager::Get().AddNativeGameplayTag(FName(TagName), FString(TEXT("(Native) ")) + FString(TagComment));
}

