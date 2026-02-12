// Fill out your copyright notice in the Description page of Project Settings.


#include "SAnimGraphNode_BlendByGameplayTag.h"

#include "AnimationGraphSchema.h"

FText USAnimGraphNode_BlendByGameplayTag::MakeFriendlyTagName(const FGameplayTag& Tag)
{
	if (!Tag.IsValid())
	{
		return FText::FromString(TEXT("Pose"));
	}

	TArray<FString> Parts;
	Tag.ToString().ParseIntoArray(Parts, TEXT("."), true);

	if (Parts.Num() >= 2)
	{
		return FText::FromString(
			Parts[Parts.Num() - 2] + TEXT(" ") + Parts[Parts.Num() - 1]
		);
	}

	return FText::FromString(Parts.Last());
}

void USAnimGraphNode_BlendByGameplayTag::AllocateDefaultPins()
{
	// Output pose
	CreateOutputPins();

	// Default Pose
	CreatePin(EGPD_Input, UAnimationGraphSchema::PC_Struct, FPoseLink::StaticStruct(), TEXT("DefaultPose"));

	// Poses por Tag
	for (int32 i = 0; i < Node.Tags.Num(); i++)
	{
		const FString PoseName =
			FString::Printf(TEXT("Pose_%d"), i);

		CreatePin(EGPD_Input, UAnimationGraphSchema::PC_Struct, FPoseLink::StaticStruct(), *PoseName);

		const FString BlendTimeName =
			FString::Printf(TEXT("BlendTime_%d"), i);

		CreatePin(EGPD_Input, UEdGraphSchema_K2::PC_Float, TEXT(""), *BlendTimeName);
	}
	
	CreatePin(EGPD_Input, UEdGraphSchema_K2::PC_Struct, FGameplayTag::StaticStruct(), TEXT("CurrentTag"));
	RefreshPinFriendlyNames();
}

void USAnimGraphNode_BlendByGameplayTag::CreateOutputPins()
{
	CreatePin( EGPD_Output, UAnimationGraphSchema::PC_Struct, FPoseLink::StaticStruct(),  TEXT("Pose"));
}

void USAnimGraphNode_BlendByGameplayTag::ReallocatePinsDuringReconstruction(TArray<UEdGraphPin*>& OldPins)
{
	AllocateDefaultPins();
	RestoreSplitPins(OldPins);
}

void USAnimGraphNode_BlendByGameplayTag::RefreshPinFriendlyNames()
{
	for (int32 i = 0; i < Node.Tags.Num(); i++)
	{
		const FString PosePinName =
			FString::Printf(TEXT("Pose_%d"), i);

		if (UEdGraphPin* PosePin = FindPin(PosePinName))
		{
			PosePin->PinFriendlyName =
				MakeFriendlyTagName(Node.Tags[i]);
		}

		const FString BlendPinName =
			FString::Printf(TEXT("BlendTime_%d"), i);

		if (UEdGraphPin* BlendPin = FindPin(BlendPinName))
		{
			BlendPin->PinFriendlyName =
				FText::Format(
					FText::FromString(TEXT("{0} Blend Time")),
					MakeFriendlyTagName(Node.Tags[i])
				);
		}
	}
}
