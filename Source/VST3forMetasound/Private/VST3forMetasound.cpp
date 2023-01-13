// Copyright Epic Games, Inc. All Rights Reserved.

#include "VST3forMetasound.h"

#define LOCTEXT_NAMESPACE "FVST3forMetasoundModule"

void FVST3forMetasoundModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
}

void FVST3forMetasoundModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FVST3forMetasoundModule, VST3forMetasound)
