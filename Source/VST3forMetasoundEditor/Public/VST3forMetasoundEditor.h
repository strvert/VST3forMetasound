#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleInterface.h"

DECLARE_LOG_CATEGORY_EXTERN(LogVST3forMetasoundEditor, Log, All);

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
