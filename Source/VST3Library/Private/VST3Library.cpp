// Copyright Epic Games, Inc. All Rights Reserved.

#include "VST3Library/Public/VST3Library.h"

#include "Logging/LogMacros.h"

#define LOCTEXT_NAMESPACE "VST3Library"

DEFINE_LOG_CATEGORY(LogVST3Library);

void FVST3LibraryModule::StartupModule()
{
}

void FVST3LibraryModule::ShutdownModule()
{
}

FVST3PluginFactoryPtr FVST3LibraryModule::FindOrCreatePluginFactory(const FString& PluginPath)
{
	if (TSharedPtr<FVST3PluginFactory>* Factory = InstancedFactories.Find(PluginPath))
	{
		return *Factory;
	}

	return InstancedFactories.Add(PluginPath, MakeShared<FVST3PluginFactory>(PluginPath));
}

FVST3LibraryModule& FVST3LibraryModule::Get()
{
	FVST3LibraryModule& Module = FModuleManager::LoadModuleChecked<FVST3LibraryModule>("VST3Library");
	return Module;
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FVST3LibraryModule, VST3LibraryModule);
