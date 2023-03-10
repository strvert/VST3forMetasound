using System.IO;
using Internal;
using UnrealBuildTool;

public class VST3forMetasoundEditor : ModuleRules
{
	public VST3forMetasoundEditor(ReadOnlyTargetRules Target) : base(Target)
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
				"VST3forMetasound",
			}
		);
	}
}