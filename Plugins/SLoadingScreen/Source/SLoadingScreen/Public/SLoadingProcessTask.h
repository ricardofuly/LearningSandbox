// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SLoadingProcessInterface.h"
#include "UObject/Object.h"
#include "SLoadingProcessTask.generated.h"

/**
 * 
 */
UCLASS()
class SLOADINGSCREEN_API USLoadingProcessTask : public UObject, public ISLoadingProcessInterface
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, meta=(WorldContext = "WorldContextObject"))
	static  USLoadingProcessTask* CreateLoadingScreenProcessTask(UObject* WorldContextObject, const FString& ShowLoadingScreenReason);

public:
	USLoadingProcessTask() { }

	UFUNCTION(BlueprintCallable)
	 void Unregister();

	UFUNCTION(BlueprintCallable)
	 void SetShowLoadingScreenReason(const FString& InReason);

	 virtual bool ShouldShowLoadingScreen(FString& OutReason) const override;
	
	FString Reason;
};
