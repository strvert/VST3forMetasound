#pragma once

#include <array>

namespace Steinberg
{
	struct PClassInfo;
	struct PClassInfoW;
	struct PClassInfo2;
}

class FClassInfo2Data
{
public:
	FClassInfo2Data(Steinberg::PClassInfo2 const& Info);
	FClassInfo2Data(Steinberg::PClassInfoW const& Info);

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

class FVST3ClassInfo
{
public:
	static constexpr uint32 CIDLength = 16;
	using FCID = std::array<int8, CIDLength>;

	FVST3ClassInfo();
	FVST3ClassInfo(const Steinberg::PClassInfo& Info);
	FVST3ClassInfo(const Steinberg::PClassInfo2& Info);
	FVST3ClassInfo(const Steinberg::PClassInfoW& Info);

	const FCID& GetCID() const { return Cid; }
	const FString& GetName() const { return Name; }
	const FString& GetCategory() const { return Category; }
	int32 GetCardinality() const { return Cardinality; }

	bool HasClassInfo2() const { return static_cast<bool>(ClassInfo2Data); }
	FClassInfo2Data const& GetClassInfo2() const { return *ClassInfo2Data; }

	bool IsEffect() const;
	bool IsInstrument() const;

private:
	FCID Cid = {};
	FString Name;
	FString Category;
	int32 Cardinality = -1;
	TOptional<FClassInfo2Data> ClassInfo2Data;
};
