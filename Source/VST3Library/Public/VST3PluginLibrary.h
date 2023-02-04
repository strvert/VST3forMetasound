#pragma once

#include "CoreMinimal.h"
#include "VST3ClassInfo.h"
#include "VST3ModuleHandle.h"
#include "VST3PluginAsset.h"
#include "VST3PluginLibrary.generated.h"

UCLASS()
class VST3LIBRARY_API UVST3PluginLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

	DECLARE_DYNAMIC_DELEGATE_OneParam(FOnVST3PluginLoaded, FVST3ModuleHandle, ModuleHandle);
	
public:

	UFUNCTION(BlueprintCallable, Category="VST3")
	static void LoadVST3Module(const UVST3PluginAsset* VST3Plugin, FOnVST3PluginLoaded LoadedDelegate);

	UFUNCTION(BlueprintCallable, Category="VST3")
	static TArray<FVST3ClassInfo> GetModuleInfoList(const FVST3ModuleHandle& InHandle);
};
