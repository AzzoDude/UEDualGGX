using UnrealBuildTool;

public class CallistoSkin : ModuleRules
{
    public CallistoSkin(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[]
        {
            "Core",
            "CoreUObject",
            "Engine",
            "RenderCore",
            "Renderer",
            "RHI"
        });

        // Tell the engine to look for our shader files in the plugin's Shaders/Private folder
        string PluginShaderDir = System.IO.Path.Combine(ModuleDirectory, "..", "Shaders");
        AddShaderSourceDirectoryMapping("/Plugin/CallistoSkin", PluginShaderDir);
    }
}