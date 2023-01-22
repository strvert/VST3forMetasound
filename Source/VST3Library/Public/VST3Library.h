// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "VST3PluginFactory.h"
#include "Modules/ModuleManager.h"

DECLARE_LOG_CATEGORY_EXTERN(LogVST3Library, Log, All);

class FVST3LibraryModule : public IModuleInterface
{
public:
	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

	static FVST3PluginFactoryPtr FindOrCreatePluginFactory(const FString& PluginPath);

	static FVST3LibraryModule& Get();

private:
	inline static TMap<FString, TSharedPtr<FVST3PluginFactory>> InstancedFactories;
};
