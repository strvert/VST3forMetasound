using System.IO;
using Internal;
using UnrealBuildTool;

public class VST3LibraryEditor : ModuleRules
{
	public VST3LibraryEditor(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				"VST3Library"
			}
		);

		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"CoreUObject",
				"Engine",
				"Slate",
				"SlateCore",
				"AssetTools",
				"UnrealEd",
			}
		);
	}
}