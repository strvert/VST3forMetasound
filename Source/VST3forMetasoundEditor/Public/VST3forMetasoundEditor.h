#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleInterface.h"

class FVST3forMetasoundEditorModule : public IModuleInterface
{
public:
	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

private:
	TArray<TSharedRef<class IAssetTypeActions>> RegisteredAssetTypeActions;

	void OnPostEngineInit();
};
