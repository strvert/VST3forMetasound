#pragma once

#include "CoreMinimal.h"
#include "VST3ModuleHandle.h"
#include "VST3PluginFactory.h"
#include "Chaos/AABB.h"
#include "Chaos/AABB.h"

DECLARE_LOG_CATEGORY_EXTERN(LogVST3Library, Log, All);

class FVST3LibraryModule : public IModuleInterface
{
public:
	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

	static std::tuple<FVST3ModuleHandle, FVST3PluginFactoryPtr> FindOrCreatePluginFactory(const FString& PluginPath);

	static FVST3LibraryModule& Get();

	static FString GetVST3HostName();

	static FVST3PluginFactoryPtr GetModuleFactory(const FVST3ModuleHandle& InHandle);

private:
	inline static TMap<FVST3ModuleHandle, FVST3PluginFactoryPtr> InstancedFactories;
	
	inline static TMap<FString, FVST3ModuleHandle> PathHandleMap;
	
	inline static const FString VST3HostName = "VST3Host";
};
