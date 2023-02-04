#include "VST3forMetasoundEditor.h"
#include "AssetToolsModule.h"

DEFINE_LOG_CATEGORY(LogVST3forMetasoundEditor);

#define LOCTEXT_NAMESPACE "FVST3forMetasoundEditorModule"

void FVST3forMetasoundEditorModule::StartupModule()
{
}

void FVST3forMetasoundEditorModule::ShutdownModule()
{
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FVST3forMetasoundEditorModule, VST3forMetasoundEditor)
