#include "VST3LibraryEditor.h"
#include "AssetTypeActions_VST3Plugin.h"
#include "IAssetTools.h"

DEFINE_LOG_CATEGORY(LogVST3LibraryEditor);

#define LOCTEXT_NAMESPACE "FVST3forMetasoundEditorModule"

void FVST3LibraryEditorModule::StartupModule()
{
	FCoreDelegates::OnPostEngineInit.AddRaw(this, &FVST3LibraryEditorModule::OnPostEngineInit);
}

void FVST3LibraryEditorModule::ShutdownModule()
{
}

void FVST3LibraryEditorModule::OnPostEngineInit()
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

IMPLEMENT_MODULE(FVST3LibraryEditorModule, VST3LibraryEditor)
