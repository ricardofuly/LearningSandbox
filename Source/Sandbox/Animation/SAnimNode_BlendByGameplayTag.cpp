// Fill out your copyright notice in the Description page of Project Settings.


#include "SAnimNode_BlendByGameplayTag.h"

void FAnimNode_BlendByGameplayTag::Initialize_AnyThread(const FAnimationInitializeContext& Context)
{
	DefaultPose.Initialize(Context);
	Poses.SetNum(Tags.Num());
	
	for (FPoseLink& Pose : Poses)
	{
		Pose.Initialize(Context);
	}
}

void FAnimNode_BlendByGameplayTag::Update_AnyThread(const FAnimationUpdateContext& Context)
{
	DefaultPose.Update(Context);

	for (FPoseLink& Pose : Poses)
	{
		Pose.Update(Context);
	}	
	
	ActivePoseIndex = INDEX_NONE;

	for (int32 i = 0; i < Tags.Num(); i++)
	{
		if (CurrentTag.MatchesTag(Tags[i]))
		{
			ActivePoseIndex = i;
			break;
		}
	}
}

void FAnimNode_BlendByGameplayTag::Evaluate_AnyThread(FPoseContext& Output)
{
	if (ActivePoseIndex != INDEX_NONE && Poses.IsValidIndex(ActivePoseIndex))
	{
		Poses[ActivePoseIndex].Evaluate(Output);
	}
	else if (IsValid(DefaultPose.StaticStruct()))
	{
		DefaultPose.Evaluate(Output);
	}
	else
	{
		Output.ResetToRefPose();
	}
}
