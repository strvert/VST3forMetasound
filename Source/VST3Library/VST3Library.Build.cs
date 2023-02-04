using System.IO;
using Internal;
using UnrealBuildTool;

public class VST3Library: ModuleRules
{
	public VST3Library(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
		bEnableUndefinedIdentifierWarnings = false;

		string MetasoundEditorPath = GetModuleDirectory("MetasoundEditor");
		PublicIncludePaths.AddRange(
			new string[]
			{
				Path.Combine(MetasoundEditorPath, "Private")
			}
		);

		string ThirdPartyPath = Path.GetFullPath(Path.Combine(PluginDirectory, "ThirdParty"));
		PrivateIncludePaths.AddRange(
			new[]
			{
				ThirdPartyPath,
				Path.Combine(ThirdPartyPath, "vst3sdk")
			}
		);


		string ConfigName = Target.Configuration == UnrealTargetConfiguration.Shipping ? "Release" : "Release";
		string Vst3SdkLibraryPath = Path.Combine(ThirdPartyPath, "vst3sdk", "lib", ConfigName);
		PublicAdditionalLibraries.AddRange(new[]
		{
			Path.Combine(Vst3SdkLibraryPath, "base.lib"),
			Path.Combine(Vst3SdkLibraryPath, "sdk.lib"),
			Path.Combine(Vst3SdkLibraryPath, "sdk_hosting.lib"),
			Path.Combine(Vst3SdkLibraryPath, "pluginterfaces.lib"),
		});
		Console.WriteLine(Path.Combine(Vst3SdkLibraryPath, "sdk_hosting.lib"));

		PrivateDefinitions.AddRange(new[]
		{
			"SMTG_RENAME_ASSERT=0",
			"SMTG_FUNKNOWN_DTOR_ASSERT=0"
		});

		if (Target.Configuration == UnrealTargetConfiguration.Shipping)
		{
			PrivateDefinitions.AddRange(new[]
			{
				"RELEASE=1"
			});
		}
		else
		{
			PrivateDefinitions.AddRange(new[]
			{
				"RELEASE=0"
			});
		}
		
		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
			}
		);


		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"CoreUObject",
				"Engine",
				"AudioExtensions"
			}
		);
	}
}