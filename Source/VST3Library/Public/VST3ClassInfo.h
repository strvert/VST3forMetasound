#pragma once

#include "CoreMinimal.h"
#include "VST3ClassInfo.generated.h"

#include <array>

namespace Steinberg
{
	struct PClassInfo;
	struct PClassInfoW;
	struct PClassInfo2;
}


USTRUCT(BlueprintType)
struct FCID
{
	GENERATED_BODY()

	static constexpr uint32 CIDLength = 16;
	std::array<char, CIDLength> Data;

	static FCID FromBytes(const char* Bytes);
	bool operator==(const FCID& Cid) const;

	FString ToString() const;
};


USTRUCT(BlueprintType, meta=(HasNativeBreak="/Script/VST3Library.VST3ClassInfoMethods.BreakVST3ClassInfoV2"))
struct FVST3ClassInfoV2
{
	GENERATED_BODY()

	/** for Blueprint */
	FVST3ClassInfoV2();

	FVST3ClassInfoV2(Steinberg::PClassInfo2 const& Info);
	FVST3ClassInfoV2(Steinberg::PClassInfoW const& Info);

	const FString& GetSubCategories() const { return SubCategories; }

	const FString& GetVendor() const { return Vendor; }

	const FString& GetVersion() const { return Version; }

	const FString& GetSDKVersion() const { return SdkVersion; }

	bool HasSubCategory(const FString& Elem) const;

private:
	FString SubCategories;
	FString Vendor;
	FString Version;
	FString SdkVersion;
};


USTRUCT(BlueprintType, meta=(HasNativeBreak="/Script/VST3Library.VST3ClassInfoMethods.BreakVST3ClassInfo"))
struct FVST3ClassInfo
{
	GENERATED_BODY()

	FVST3ClassInfo();
	FVST3ClassInfo(const Steinberg::PClassInfo& Info);
	FVST3ClassInfo(const Steinberg::PClassInfo2& Info);
	FVST3ClassInfo(const Steinberg::PClassInfoW& Info);

	const FCID& GetCID() const { return Cid; }

	const FString& GetName() const { return Name; }

	const FString& GetCategory() const { return Category; }

	int32 GetCardinality() const { return Cardinality; }

	bool HasClassInfo2() const { return static_cast<bool>(ClassInfo2Data); }

	FVST3ClassInfoV2 const& GetClassInfo2() const { return *ClassInfo2Data; }

	bool IsEffect() const;

	bool IsInstrument() const;

private:
	FCID Cid = {};
	FString Name;
	FString Category;
	int32 Cardinality = -1;
	TOptional<FVST3ClassInfoV2> ClassInfo2Data;
};


UCLASS()
class UVST3ClassInfoLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure, Category="VST3", meta = (NativeBreakFunc))
	static void BreakVST3ClassInfo(const FVST3ClassInfo& ClassInfo, FCID& CID, FString& Name, FString& Category,
	                               int32& Cardinality, bool& IsEffect, bool& IsInstrument, bool& HasClassInfoV2);

	UFUNCTION(BlueprintPure, Category="VST3", meta = (NativeBreakFunc))
	static void BreakVST3ClassInfoV2(const FVST3ClassInfoV2& ClassInfoV2, FString& SubCategories, FString& Vendor,
	                                 FString& Version, FString& SDKVersion);

	UFUNCTION(BlueprintPure, Category="VST3", meta = (CompactNodeTitle="->", BlueprintAutocast))
	static FString Conv_CIDToString(const FCID& InCID);

	UFUNCTION(BlueprintPure, Category="VST3")
	static FVST3ClassInfoV2 const& GetClassInfo2(const FVST3ClassInfo& ClassInfo) { return ClassInfo.GetClassInfo2(); }

	UFUNCTION(BlueprintPure, Category="VST3")
	static bool HasSubCategory(const FVST3ClassInfoV2& ClassInfo2, const FString& Elem);
};
