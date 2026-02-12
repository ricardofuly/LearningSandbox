// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "SAnimNode_BlendByGameplayTag.generated.h"

/**
 * 
 */
USTRUCT(BlueprintInternalUseOnly)
struct FAnimNode_BlendByGameplayTag  : public FAnimNode_Base
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Tags")
	FGameplayTag CurrentTag;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Poses")
	TArray<FGameplayTag> Tags;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Poses")
	TArray<FPoseLink> Poses;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Settings")
	float BlendTime = 0.1f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Poses")
	FPoseLink DefaultPose;
	
	virtual void Initialize_AnyThread(const FAnimationInitializeContext& Context) override;
	virtual void Update_AnyThread(const FAnimationUpdateContext& Context) override;
	virtual void Evaluate_AnyThread(FPoseContext& Output) override;
	
private:
	
	int32 ActivePoseIndex = INDEX_NONE;
};
