#include "VST3ClassInfo.h"
#include "vst3sdk/pluginterfaces/base/ipluginbase.h"

FCID FCID::FromBytes(const char* Bytes)
{
	FCID CID;
	std::copy_n(Bytes, CIDLength, CID.Data.begin());
	return CID;
}

bool FCID::operator==(const FCID& Cid) const
{
	return this->Data == Cid.Data;
}

FString FCID::ToString() const
{
	FString Str;
	static constexpr uint8 Hyphens[] = {7, 11, 15, 19};
	const TArrayView<const uint8> HyphensView(Hyphens);

	uint8 Index = 0;
	for (const char& Byte : Data)
	{
		Str += FString::FromHexBlob(reinterpret_cast<const uint8*>(&Byte), 1);
		if (HyphensView.Contains(Index))
		{
			Str += FString("-");
		}
		Index++;
	}
	return Str;
}

FVST3ClassInfoV2::FVST3ClassInfoV2()
{
}

FVST3ClassInfoV2::FVST3ClassInfoV2(Steinberg::PClassInfo2 const& Info):
	SubCategories(UTF8_TO_TCHAR(Info.subCategories)),
	Vendor(WCHAR_TO_TCHAR(Info.vendor)),
	Version(WCHAR_TO_TCHAR(Info.version)),
	SdkVersion(WCHAR_TO_TCHAR(Info.sdkVersion))
{
}

FVST3ClassInfoV2::FVST3ClassInfoV2(Steinberg::PClassInfoW const& Info):
	SubCategories(UTF8_TO_TCHAR(Info.subCategories)),
	Vendor(WCHAR_TO_TCHAR(Info.vendor)),
	Version(WCHAR_TO_TCHAR(Info.version)),
	SdkVersion(WCHAR_TO_TCHAR(Info.sdkVersion))
{
}

bool FVST3ClassInfoV2::HasSubCategory(const FString& Elem) const
{
	TArray<FString> Out;
	SubCategories.ParseIntoArrayWS(Out, TEXT("|"));
	return Out.ContainsByPredicate([&](const FString& Str)
	{
		return Str.Equals(Elem, ESearchCase::IgnoreCase);
	});
}

FVST3ClassInfo::FVST3ClassInfo()
{
}

FVST3ClassInfo::FVST3ClassInfo(const Steinberg::PClassInfo& Info):
	Cid(),
	Name(WCHAR_TO_TCHAR(Info.name)),
	Category(WCHAR_TO_TCHAR(Info.category)),
	Cardinality(Info.cardinality)
{
	Cid = FCID::FromBytes(Info.cid);
}

FVST3ClassInfo::FVST3ClassInfo(const Steinberg::PClassInfo2& Info):
	Cid(),
	Name(WCHAR_TO_TCHAR(Info.name)),
	Category(WCHAR_TO_TCHAR(Info.category)),
	Cardinality(Info.cardinality),
	ClassInfo2Data(Info)
{
	Cid = FCID::FromBytes(Info.cid);
}

FVST3ClassInfo::FVST3ClassInfo(const Steinberg::PClassInfoW& Info):
	Cid(),
	Name(WCHAR_TO_TCHAR(Info.name)),
	Category(UTF8_TO_TCHAR(Info.category)),
	Cardinality(Info.cardinality),
	ClassInfo2Data(Info)
{
	Cid = FCID::FromBytes(Info.cid);
}

bool FVST3ClassInfo::IsEffect() const
{
	return HasClassInfo2() && GetClassInfo2().HasSubCategory("fx");
}

bool FVST3ClassInfo::IsInstrument() const
{
	return HasClassInfo2() && GetClassInfo2().HasSubCategory("instrument");
}

bool UVST3ClassInfoLibrary::HasSubCategory(const FVST3ClassInfoV2& ClassInfo2, const FString& Elem)
{
	return ClassInfo2.HasSubCategory(Elem);
}

void UVST3ClassInfoLibrary::BreakVST3ClassInfo(const FVST3ClassInfo& ClassInfo, FCID& CID, FString& Name,
                                               FString& Category, int32& Cardinality,
                                               bool& IsEffect, bool& IsInstrument, bool& HasClassInfoV2)
{
	CID = ClassInfo.GetCID();
	Name = ClassInfo.GetName();
	Category = ClassInfo.GetCategory();
	Cardinality = ClassInfo.GetCardinality();
	IsEffect = ClassInfo.IsEffect();
	IsInstrument = ClassInfo.IsInstrument();
	HasClassInfoV2 = ClassInfo.HasClassInfo2();
}

void UVST3ClassInfoLibrary::BreakVST3ClassInfoV2(const FVST3ClassInfoV2& ClassInfoV2, FString& SubCategories,
                                                 FString& Vendor, FString& Version, FString& SDKVersion)
{
	SubCategories = ClassInfoV2.GetSubCategories();
	Vendor = ClassInfoV2.GetVendor();
	Version = ClassInfoV2.GetVersion();
	SDKVersion = ClassInfoV2.GetSDKVersion();
}

FString UVST3ClassInfoLibrary::Conv_CIDToString(const FCID& InCID)
{
	return InCID.ToString();
}
