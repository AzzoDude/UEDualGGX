#include "CallistoSkinModule.h"
#include "Materials/Material.h"
#include "MaterialDomain.h"
#include "ShadingModelTypes.h"
#include "MaterialShaderType.h"
#include "MaterialShared.h"
#include "ShaderCompiler.h"
#include "Interfaces/IPluginManager.h"

DEFINE_LOG_CATEGORY_STATIC(LogCallistoSkin, Log, All);

void FCallistoSkinModule::StartupModule()
{
    // Register the custom shading model
    CallistoShadingModelHandle = FShadingModelHandle::AddShadingModel(
        TEXT("Callisto Skin"),
        FText::FromString("Callisto Skin"),
        EMaterialShadingModel::MSM_Num,
        EMaterialDomain::MD_Surface,
        true,   // bIsForwardShadingModel
        true,   // bIsDeferredShadingModel
        FShadingModelAttributes()
    );

    check(CallistoShadingModelHandle.IsValid());

    FString PluginShaderDir = IPluginManager::Get().FindPlugin(TEXT("CallistoSkin"))->GetBaseDir() / TEXT("Shaders");
    AddShaderSourceDirectoryMapping(TEXT("/Plugin/CallistoSkin"), PluginShaderDir);

    UE_LOG(LogCallistoSkin, Log, TEXT("Callisto Skin shading model registered successfully."));
}

void FCallistoSkinModule::ShutdownModule()
{
    UE_LOG(LogCallistoSkin, Log, TEXT("Callisto Skin module shutdown."));
}

IMPLEMENT_MODULE(FCallistoSkinModule, CallistoSkin)