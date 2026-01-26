#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

class IDetailsView;
class UAnimNotifyBatchToolObject;

class FAnimNotifyBatchToolModule : public IModuleInterface
{
public:
    virtual void StartupModule() override;
    virtual void ShutdownModule() override;

private:
    // 编辑器入口（Window/Tools 菜单添加“Anim Notify Batch Tool”）。
    void RegisterMenus();
    void UnregisterMenus();

    // 面板
    TSharedRef<class SDockTab> SpawnPluginTab(const class FSpawnTabArgs& SpawnTabArgs);

private:
    static const FName TabName;

private:
    TStrongObjectPtr<UAnimNotifyBatchToolObject> ToolObject;
    TSharedPtr<IDetailsView> DetailsView;
};
