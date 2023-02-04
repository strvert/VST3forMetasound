#include "VST3forMetasound.h"

#include "MetasoundDataTypeRegistrationMacro.h"
#include "VST3PluginAssetProxy.h"
#include "VST3PluginLibrary.h"

#define LOCTEXT_NAMESPACE "FVST3forMetasoundModule"

DEFINE_LOG_CATEGORY(LogVST3forMetasound);

REGISTER_METASOUND_DATATYPE(FVST3PluginAsset, "VST3PluginAsset", Metasound::ELiteralType::UObjectProxy,
                            UVST3PluginAsset);

void FVST3forMetasoundModule::StartupModule()
{
	FMetasoundFrontendRegistryContainer::Get()->RegisterPendingNodes();

	// FVST3ModuleHandle ModuleHandle = UVST3PluginLibrary::LoadVST3Module(
	// 	R"(E:\UnrealProjects\Metasounds\Plugins\VST3forMetasound\ThirdParty\vst3sdk\build\VST3\Release\noteexpressionsynth.vst3\Contents\x86_64-win\noteexpressionsynth.vst3)"
	// );

}

void FVST3forMetasoundModule::ShutdownModule()
{
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FVST3forMetasoundModule, VST3forMetasound)
