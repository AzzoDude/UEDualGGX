#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleInterface.h"
#include "MaterialShadingModel.h"

class FCallistoSkinModule : public IModuleInterface
{
public:
    virtual void StartupModule() override;
    virtual void ShutdownModule() override;

private:
    FShadingModelHandle CallistoShadingModelHandle;
};