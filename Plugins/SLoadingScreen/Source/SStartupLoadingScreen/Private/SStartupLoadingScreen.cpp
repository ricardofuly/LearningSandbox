#include "SStartupLoadingScreen.h"

#include "PreLoadScreenManager.h"

#define LOCTEXT_NAMESPACE "FSStartupLoadingScreenModule"

void FSStartupLoadingScreenModule::StartupModule()
{
	if (!IsRunningDedicatedServer())
	{
		PreLoadScreen = MakeShared<FPreLoadScreen>();
		PreLoadScreen->Init();

		if (!GIsEditor && FApp::CanEverRender() && FPreLoadScreenManager::Get())
		{
			FPreLoadScreenManager::Get()->RegisterPreLoadScreen(PreLoadScreen);
			FPreLoadScreenManager::Get()->OnPreLoadScreenManagerCleanUp.AddRaw(this, &FSStartupLoadingScreenModule::OnPreLoadScreenManagerCleanUp);
		}
	}
}

void FSStartupLoadingScreenModule::ShutdownModule()
{
    
}

bool FSStartupLoadingScreenModule::IsGameModule() const
{
	return true;
}

void FSStartupLoadingScreenModule::OnPreLoadScreenManagerCleanUp()
{
	PreLoadScreen.Reset();
	ShutdownModule();
}

#undef LOCTEXT_NAMESPACE
    
IMPLEMENT_MODULE(FSStartupLoadingScreenModule, SStartupLoadingScreen)