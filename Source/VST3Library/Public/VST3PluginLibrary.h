#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "VST3PluginLibrary.generated.h"

UCLASS()
class VST3LIBRARY_API UVST3PluginLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:

	UFUNCTION(BlueprintCallable, Category="VST3")
	static bool LoadVST3Module(const FString& Path);
};
