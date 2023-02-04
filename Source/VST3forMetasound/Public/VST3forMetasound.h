#pragma once

#include "CoreMinimal.h"
#include "VST3PluginAssetProxy.h"
#include "MetasoundDataReferenceMacro.h"
#include "Modules/ModuleManager.h"

DECLARE_LOG_CATEGORY_EXTERN(LogVST3forMetasound, Log, All);

class FVST3forMetasoundModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};

DECLARE_METASOUND_DATA_REFERENCE_TYPES(FVST3PluginAsset, VST3FORMETASOUND_API, FVST3PluginAssetTypeInfo,
                                       FVST3PluginAssetReadRef, FVST3PluginAssetWriteRef)
