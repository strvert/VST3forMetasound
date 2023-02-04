#include "VST3PluginAssetProxy.h"
#include "VST3PluginAsset.h"


TUniquePtr<Audio::IProxyData> UVST3PluginAsset::CreateNewProxyData(const Audio::FProxyDataInitParams& InitParams)
{
	return MakeUnique<FVST3PluginProxy>(this);
}

FVST3PluginProxy::FVST3PluginProxy(UVST3PluginAsset* InVST3Plugin)
{
	if (InVST3Plugin)
	{
		PluginPath = InVST3Plugin->PluginPath.FilePath;
	}
}

Audio::IProxyDataPtr FVST3PluginProxy::Clone() const
{
	return MakeUnique<FVST3PluginProxy>(*this);
}
