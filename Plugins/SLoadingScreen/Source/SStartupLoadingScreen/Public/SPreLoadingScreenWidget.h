#pragma once

#include "CoreMinimal.h"
#include "UObject/GCObject.h"
#include "Widgets/Accessibility/SlateWidgetAccessibleTypes.h"
#include "Widgets/SCompoundWidget.h" 

class SPreLoadingScreenWidget : public SCompoundWidget, public  FGCObject
{
public:
	
	SLATE_BEGIN_ARGS(SPreLoadingScreenWidget) {}
	SLATE_END_ARGS()
	
	void Construct(const FArguments& InArgs);
	
	//~ Begin FGCObject interface
	virtual void AddReferencedObjects(FReferenceCollector& Collector) override;
	virtual FString GetReferencerName() const override;
	//~ End FGCObject interface	
};
