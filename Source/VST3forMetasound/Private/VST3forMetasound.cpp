// Copyright Epic Games, Inc. All Rights Reserved.

#include "VST3forMetasound.h"

#include "MetasoundFrontendRegistries.h"

#define LOCTEXT_NAMESPACE "FVST3forMetasoundModule"

void FVST3forMetasoundModule::StartupModule()
{
	FMetasoundFrontendRegistryContainer::Get()->RegisterPendingNodes();

	FPropertyEditorModule& PropertyModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");
}

void FVST3forMetasoundModule::ShutdownModule()
{
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FVST3forMetasoundModule, VST3forMetasound)
