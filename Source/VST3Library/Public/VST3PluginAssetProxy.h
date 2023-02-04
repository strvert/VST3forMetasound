#pragma once

#include "CoreMinimal.h"
#include "IAudioProxyInitializer.h"
#include "Engine/DataAsset.h"


class UVST3PluginAsset;
class FVST3PluginProxy;

using FVST3PluginProxyPtr = TSharedPtr<FVST3PluginProxy, ESPMode::ThreadSafe>;

class VST3LIBRARY_API FVST3PluginProxy final : public Audio::TProxyData<FVST3PluginProxy>
{
public:
	IMPL_AUDIOPROXY_CLASS(FVST3PluginProxy);

	explicit FVST3PluginProxy(UVST3PluginAsset* InVST3Plugin);

	FVST3PluginProxy(const FVST3PluginProxy& Other) = default;

	virtual ~FVST3PluginProxy() override
	{
	}

	virtual Audio::IProxyDataPtr Clone() const override;

	const FString& GetPluginPath() const
	{
		return PluginPath;
	}

private:
	FString PluginPath;
};


class VST3LIBRARY_API FVST3PluginAsset
{
	FVST3PluginProxyPtr VST3PluginProxy;

public:
	FVST3PluginAsset() = default;
	FVST3PluginAsset(const FVST3PluginAsset&) = default;
	FVST3PluginAsset& operator=(const FVST3PluginAsset& Other) = default;

	FVST3PluginAsset(const TUniquePtr<Audio::IProxyData>& InInitData)
	{
		if (InInitData.IsValid())
		{
			if (InInitData->CheckTypeCast<FVST3PluginProxy>())
			{
				VST3PluginProxy
					= MakeShared<FVST3PluginProxy, ESPMode::ThreadSafe>(InInitData->GetAs<FVST3PluginProxy>());
			}
		}
	}

	const FVST3PluginProxyPtr& GetVST3PluginProxy() const
	{
		return VST3PluginProxy;
	}
};
