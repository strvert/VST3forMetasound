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

std::tuple<FVST3ModuleHandle, FVST3PluginFactoryPtr> FVST3LibraryModule::FindOrCreatePluginFactory(
	const FString& PluginPath)
{
	if (FVST3ModuleHandle* HandlePtr = PathHandleMap.Find(PluginPath))
	{
		return {*HandlePtr, *InstancedFactories.Find(*HandlePtr)};
	}

	const FVST3ModuleHandle NewHandle = FVST3ModuleHandle::NewHandle();
	FVST3PluginFactoryPtr NewFactory
		= InstancedFactories.Emplace(NewHandle, MakeShared<FVST3PluginFactory>(PluginPath));
	PathHandleMap.Emplace(PluginPath, NewHandle);
	return {NewHandle, NewFactory};
}

FVST3LibraryModule& FVST3LibraryModule::Get()
{
	FVST3LibraryModule& Module = FModuleManager::LoadModuleChecked<FVST3LibraryModule>("VST3Library");
	return Module;
}

FString FVST3LibraryModule::GetVST3HostName()
{
	return VST3HostName;
}

FVST3PluginFactoryPtr FVST3LibraryModule::GetModuleFactory(const FVST3ModuleHandle& InHandle)
{
	if (FVST3PluginFactoryPtr* Factory = InstancedFactories.Find(InHandle))
	{
		return *Factory;
	}
	return nullptr;
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FVST3LibraryModule, VST3LibraryModule);
