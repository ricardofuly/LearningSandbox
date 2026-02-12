// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SAnimNode_BlendByGameplayTag.h"
#include "Editor/AnimGraph/Public/AnimGraphNode_Base.h"
#include "SAnimGraphNode_BlendByGameplayTag.generated.h"

/**
 * 
 */
UCLASS()
class SANDBOX_API USAnimGraphNode_BlendByGameplayTag : public UAnimGraphNode_Base
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, Category="Settings")
	FAnimNode_BlendByGameplayTag Node;
	
	static FText MakeFriendlyTagName(const FGameplayTag& Tag);
	
	virtual void AllocateDefaultPins() override;
	virtual void CreateOutputPins() override;
	virtual void ReallocatePinsDuringReconstruction(TArray<UEdGraphPin*>& OldPins) override;
	
	void RefreshPinFriendlyNames();

	virtual FText GetNodeTitle(
		ENodeTitleType::Type TitleType) const override
	{
		return FText::FromString("Blend Poses by Gameplay Tag");
	}
};
