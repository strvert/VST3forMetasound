// Copyright Epic Games, Inc. All Rights Reserved.

using System.IO;
using UnrealBuildTool;

public class VST3forMetasound : ModuleRules
{
	public VST3forMetasound(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicIncludePaths.AddRange(
			new string[]
			{
				// ... add public include paths required here ...
			}
		);

		string ThirdPartyPath = Path.GetFullPath(Path.Combine(PluginDirectory, "./ThirdParty/"));
		PrivateIncludePaths.AddRange(
			new[]
			{
				ThirdPartyPath
			}
		);


		string ConfigName = Target.Configuration == UnrealTargetConfiguration.Shipping ? "Release" : "Debug";
		string Vst3SdkLibraryPath = Path.Combine(ThirdPartyPath, "vst3sdk", "lib", ConfigName);
		System.Console.WriteLine(Vst3SdkLibraryPath);
		PublicAdditionalLibraries.AddRange(new[]
		{
			Path.Combine(Vst3SdkLibraryPath, "base.lib"),
		});

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
				"Slate",
				"SlateCore",
			}
		);
	}
}