using System.IO;
using Internal;
using UnrealBuildTool;

public class VST3forMetasound : ModuleRules
{
	public VST3forMetasound(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
		
		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				"MetasoundGraphCore", "VST3Library",
			}
		);


		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"CoreUObject",
				"Engine",
				"Slate",
				"SlateCore",
				"AudioExtensions",
				"MetasoundGraphCore",
				"MetasoundEditor",
				"MetasoundFrontend",
				"MetasoundEngine",
				"MetasoundStandardNodes",
				"AudioSynesthesia",
				"VST3Library"
			}
		);
	}
}