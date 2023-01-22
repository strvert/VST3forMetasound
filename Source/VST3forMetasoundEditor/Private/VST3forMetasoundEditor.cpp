#include "VST3forMetasoundEditor.h"
#include "AssetTypeActions_VST3Plugin.h"
#include "IAssetTools.h"

DEFINE_LOG_CATEGORY(LogVST3forMetasoundEditor);

#define LOCTEXT_NAMESPACE "FVST3forMetasoundEditorModule"

void FVST3forMetasoundEditorModule::StartupModule()
{
	FCoreDelegates::OnPostEngineInit.AddRaw(this, &FVST3forMetasoundEditorModule::OnPostEngineInit);
}

void FVST3forMetasoundEditorModule::ShutdownModule()
{
}

void FVST3forMetasoundEditorModule::OnPostEngineInit()
{
	auto RegisterAssetTypeAction = [this](IAssetTools& AssetTools,
	                                      const TSharedRef<IAssetTypeActions>& InAssetTypeAction)
	{
		RegisteredAssetTypeActions.Add(InAssetTypeAction);
		AssetTools.RegisterAssetTypeActions(InAssetTypeAction);
	};

	IAssetTools& AssetTools = FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools").Get();

	RegisterAssetTypeAction(AssetTools, MakeShared<FAssetTypeActions_VST3Plugin>());
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FVST3forMetasoundEditorModule, VST3forMetasoundEditor)
