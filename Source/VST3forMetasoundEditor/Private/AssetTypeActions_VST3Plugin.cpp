#include "AssetTypeActions_VST3Plugin.h"

#include "VST3forMetasoundEditor.h"
#include "VST3forMetasound/Public/VST3PluginAsset.h"

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

#undef LOCTEXT_NAMESPACE
