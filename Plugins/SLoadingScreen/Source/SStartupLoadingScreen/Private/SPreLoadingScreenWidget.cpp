#include "SPreLoadingScreenWidget.h"
#include "Widgets/Layout/SBorder.h"

class FReferenceCollector;

void SPreLoadingScreenWidget::Construct(const FArguments& InArgs)
{
	ChildSlot
	[
		SNew(SBorder)
		.BorderImage(FCoreStyle::Get().GetBrush("WhiteBrush"))
		.BorderBackgroundColor(FLinearColor::Black)
		.Padding(0)
	];
}

void SPreLoadingScreenWidget::AddReferencedObjects(FReferenceCollector& Collector)
{
}

FString SPreLoadingScreenWidget::GetReferencerName() const
{
	return TEXT("SPreLoadingScreenWidget");
}
