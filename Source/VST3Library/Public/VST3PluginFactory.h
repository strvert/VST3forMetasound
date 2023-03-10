#pragma once

#include "CoreMinimal.h"
#include "VST3ClassInfo.h"

namespace Steinberg
{
	struct PFactoryInfo;
}

class UVST3Plugin;
class FVST3PluginFactory;
using FVST3PluginFactoryPtr = TSharedPtr<FVST3PluginFactory>;

class FFactoryInfo;

class VST3LIBRARY_API FVST3PluginFactory
{
public:
	FVST3PluginFactory(const FString& ModulePath);
	~FVST3PluginFactory();

	const FFactoryInfo& GetFactoryInfo() const;

	size_t GetComponentCount() const;

	const FVST3ClassInfo& GetComponentInfo(size_t Index) const;

	TObjectPtr<UVST3Plugin> CreateByIndex(size_t Index) const;

	TObjectPtr<UVST3Plugin> CreateByID(const FCID& ComponentId) const;

	uint32 GetNumLoadedPlugins() const;

private:
	class FImpl;
	TUniquePtr<FImpl> PImpl;
};

class VST3LIBRARY_API FFactoryInfo
{
public:
	FFactoryInfo();

	FFactoryInfo(const Steinberg::PFactoryInfo& Info);

	bool IsDiscardable() const;
	bool IsLicenseCheck() const;
	bool IsComponentNonDiscardable() const;
	bool IsUnicode() const;

	FString GetVendor() const;
	FString GetURL() const;
	FString GetEmail() const;

private:
	FString Vendor;
	FString Url;
	FString Email;
	int32 Flags;
};
