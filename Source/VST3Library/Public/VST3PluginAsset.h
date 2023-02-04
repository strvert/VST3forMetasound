#pragma once

#include "CoreMinimal.h"
#include "VST3PluginAsset.generated.h"


UCLASS(BlueprintType)
class VST3LIBRARY_API UVST3PluginAsset : public UDataAsset, public IAudioProxyDataFactory
{
	GENERATED_BODY()

public:
	virtual TUniquePtr<Audio::IProxyData> CreateNewProxyData(const Audio::FProxyDataInitParams& InitParams) override;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Plugin Properties")
	FFilePath PluginPath;
};

