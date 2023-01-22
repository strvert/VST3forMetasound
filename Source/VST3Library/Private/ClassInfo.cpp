#include "ClassInfo.h"
#include "vst3sdk/pluginterfaces/base/ipluginbase.h"

FClassInfo2Data::FClassInfo2Data(Steinberg::PClassInfo2 const& Info):
	SubCategories(UTF8_TO_TCHAR(Info.subCategories)),
	Vendor(WCHAR_TO_TCHAR(Info.vendor)),
	Version(WCHAR_TO_TCHAR(Info.version)),
	SdkVersion(WCHAR_TO_TCHAR(Info.sdkVersion))
{
}

FClassInfo2Data::FClassInfo2Data(Steinberg::PClassInfoW const& Info):
	SubCategories(UTF8_TO_TCHAR(Info.subCategories)),
	Vendor(WCHAR_TO_TCHAR(Info.vendor)),
	Version(WCHAR_TO_TCHAR(Info.version)),
	SdkVersion(WCHAR_TO_TCHAR(Info.sdkVersion))
{
}

bool FClassInfo2Data::HasSubCategory(const FString& Elem) const
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
	std::copy_n(Info.cid, CIDLength, Cid.begin());
}

FVST3ClassInfo::FVST3ClassInfo(const Steinberg::PClassInfo2& Info):
	Cid(),
	Name(WCHAR_TO_TCHAR(Info.name)),
	Category(WCHAR_TO_TCHAR(Info.category)),
	Cardinality(Info.cardinality),
	ClassInfo2Data(Info)
{
	std::copy_n(Info.cid, CIDLength, Cid.begin());
}

FVST3ClassInfo::FVST3ClassInfo(const Steinberg::PClassInfoW& Info):
	Cid(),
	Name(WCHAR_TO_TCHAR(Info.name)),
	Category(UTF8_TO_TCHAR(Info.category)),
	Cardinality(Info.cardinality),
	ClassInfo2Data(Info)
{
	std::copy_n(Info.cid, CIDLength, Cid.begin());
}

bool FVST3ClassInfo::IsEffect() const
{
	return HasClassInfo2() && GetClassInfo2().HasSubCategory("fx");
}

bool FVST3ClassInfo::IsInstrument() const
{
	return HasClassInfo2() && GetClassInfo2().HasSubCategory("instrument");
}
