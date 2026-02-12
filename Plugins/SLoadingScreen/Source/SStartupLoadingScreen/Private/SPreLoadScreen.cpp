#include "SPreLoadScreen.h"

#include "SPreLoadingScreenWidget.h"

void FPreLoadScreen::Init()
{
	if (!GIsEditor && FApp::CanEverRender())
	{
		EngineLoadingWidget = SNew(SPreLoadingScreenWidget);
	}
}
