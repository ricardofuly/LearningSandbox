// Fill out your copyright notice in the Description page of Project Settings.


#include "SLoadingProcessTask.h"

#include "SLoadingScreenManager.h"

USLoadingProcessTask* USLoadingProcessTask::CreateLoadingScreenProcessTask(UObject* WorldContextObject,
                                                                           const FString& ShowLoadingScreenReason)
{
	UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull);
	UGameInstance* GameInstance = World ? World->GetGameInstance() : nullptr;
	USLoadingScreenManager* LoadingScreenManager = GameInstance ? GameInstance->GetSubsystem<USLoadingScreenManager>() : nullptr;

	if (LoadingScreenManager)
	{
		USLoadingProcessTask* NewLoadingTask = NewObject<USLoadingProcessTask>(LoadingScreenManager);
		NewLoadingTask->SetShowLoadingScreenReason(ShowLoadingScreenReason);

		LoadingScreenManager->RegisterLoadingProcessor(NewLoadingTask);
		
		return NewLoadingTask;
	}

	return nullptr;
}

void USLoadingProcessTask::Unregister()
{
	USLoadingScreenManager* LoadingScreenManager = Cast<USLoadingScreenManager>(GetOuter());
	LoadingScreenManager->UnregisterLoadingProcessor(this);
}

void USLoadingProcessTask::SetShowLoadingScreenReason(const FString& InReason)
{
	Reason = InReason;
}

bool USLoadingProcessTask::ShouldShowLoadingScreen(FString& OutReason) const
{
	OutReason = Reason;
	return true;
}
