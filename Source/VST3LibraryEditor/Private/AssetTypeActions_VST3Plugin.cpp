#include "AssetTypeActions_VST3Plugin.h"

#include "VST3LibraryEditor.h"
#include "Toolkits/BaseToolkit.h"
#include "VST3PluginAsset.h"

#define LOCTEXT_NAMESPACE "AssetTypeActions"

const TArray<FText>& FAssetTypeActions_VST3Plugin::GetSubMenus() const
{
	// static TArray SubMenu = {
	// 	LOCTEXT("VST3PluginAssetCategory", "VST3")
	// };
	// return SubMenu;
	return FAssetTypeActions_DataAsset::GetSubMenus();
}

uint32 FAssetTypeActions_VST3Plugin::GetCategories()
{
	return EAssetTypeCategories::Sounds;
}

FText FAssetTypeActions_VST3Plugin::GetAssetDescription(const FAssetData& AssetData) const
{
	return LOCTEXT("AssetVST3PluginDescription", "VST3プラグインのセッティングを行うアセット");
}

UClass* FAssetTypeActions_VST3Plugin::GetSupportedClass() const
{
	return UVST3PluginAsset::StaticClass();
}

void FAssetTypeActions_VST3Plugin::OpenAssetEditor(const TArray<UObject*>& InObjects,
                                                   TSharedPtr<IToolkitHost> EditWithinLevelEditor)
{
	const TSharedRef<FSimpleAssetEditor> AssetEditor
		= FSimpleAssetEditor::CreateEditor(EToolkitMode::Standalone, EditWithinLevelEditor, InObjects);
	TArray<TWeakObjectPtr<UVST3PluginAsset>> SettingAssets = GetTypedWeakObjectPtrs<UVST3PluginAsset>(InObjects);

	if (SettingAssets.Num() == 1)
	{
		const TSharedRef<FExtender> ToolbarExtender = MakeShared<FExtender>();
		ToolbarExtender->AddToolBarExtension(
			"Asset",
			EExtensionHook::After,
			AssetEditor->GetToolkitCommands(),
			FToolBarExtensionDelegate::CreateLambda([this](FToolBarBuilder& Builder)
			{
				Builder.AddToolBarButton(
					FUIAction(FExecuteAction::CreateLambda([]
					{
						
					})),
					NAME_None,
					LOCTEXT("OpenVSTEditor", "Open VST Editor"),
					LOCTEXT("OpenVSTEditor", "Open VST Editor"),
					FSlateIcon(FAppStyle::GetAppStyleSetName(), "Icons.OpenInExternalEditor"));
			}));

		AssetEditor->AddToolbarExtender(ToolbarExtender);
		AssetEditor->RegenerateMenusAndToolbars();
	}
}

#undef LOCTEXT_NAMESPACE
