#pragma once

#include "AssetTypeActions/AssetTypeActions_DataAsset.h"

class FAssetTypeActions_VST3Plugin : public FAssetTypeActions_DataAsset
{
public:
	//~ Begin IAssetTypeActions Implementation
	virtual FText GetName() const override { return NSLOCTEXT("AssetTypeActions", "AssetTypeActions_VST3Plugin", "VST3 Plugin"); }
	virtual FColor GetTypeColor() const override { return FColor(97, 97, 85); }
	virtual const TArray<FText>& GetSubMenus() const override;
	virtual uint32 GetCategories() override;
	virtual FText GetAssetDescription(const FAssetData& AssetData) const override;
	virtual UClass* GetSupportedClass() const override;
	//~ End IAssetTypeActions Implementation
};
