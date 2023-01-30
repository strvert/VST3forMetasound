#pragma once

#include "CoreMinimal.h"
#include "VST3ClassInfo.h"
#include "VST3ModuleHandle.h"
#include "VST3PluginLibrary.generated.h"

UCLASS()
class VST3LIBRARY_API UVST3PluginLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:

	UFUNCTION(BlueprintCallable, Category="VST3")
	static FVST3ModuleHandle LoadVST3Module(const FString& Path);

	UFUNCTION(BlueprintCallable, Category="VST3")
	static TArray<FVST3ClassInfo> GetModuleInfoList(const FVST3ModuleHandle& InHandle);
};
