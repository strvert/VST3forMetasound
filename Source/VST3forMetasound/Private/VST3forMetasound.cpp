#include "VST3forMetasound.h"

#include "MetasoundDataTypeRegistrationMacro.h"
#include "VST3PluginAsset.h"

#define LOCTEXT_NAMESPACE "FVST3forMetasoundModule"

DEFINE_LOG_CATEGORY(LogVST3forMetasound);

REGISTER_METASOUND_DATATYPE(FVST3PluginAsset, "VST3PluginAsset", Metasound::ELiteralType::UObjectProxy, UVST3PluginAsset);

void FVST3forMetasoundModule::StartupModule()
{
	FMetasoundFrontendRegistryContainer::Get()->RegisterPendingNodes();
}

void FVST3forMetasoundModule::ShutdownModule()
{
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FVST3forMetasoundModule, VST3forMetasound)
