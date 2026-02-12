#pragma once

#include "CoreMinimal.h"
#include "SPreLoadScreen.h"
#include "Modules/ModuleManager.h"

class FSStartupLoadingScreenModule : public IModuleInterface
{
public:
    
    /** IModuleInterface implementation */
    virtual void StartupModule() override;
    virtual void ShutdownModule() override;
    bool IsGameModule() const override;
    
private:
    void OnPreLoadScreenManagerCleanUp();
    
    TSharedPtr<FPreLoadScreen> PreLoadScreen;
};
