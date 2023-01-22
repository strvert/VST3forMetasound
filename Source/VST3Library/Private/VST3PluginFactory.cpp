#include "VST3PluginFactory.h"

#include "VST3MAUtils.h"
#include "public.sdk/source/vst/hosting/module.h"
#include "pluginterfaces/base/ipluginbase.h"

class FVST3PluginFactory::FImpl
{
public:
	FImpl(const FString& ModulePath)
	{
		const std::string Path = TCHAR_TO_UTF8(*ModulePath);

		std::string ErrorDesc;
		std::shared_ptr<VST3::Hosting::Module> Mod = VST3::Hosting::Module::create(Path, ErrorDesc);

		if (!Mod)
		{
			return;
		}


		maybe_vstma_unique_ptr<Steinberg::IPluginFactory> MaybeFactory
			= queryInterface<Steinberg::IPluginFactory>(Mod->getFactory().get());
		if (!MaybeFactory)
		{
			return;
		}

		std::unique_ptr<Steinberg::IPluginFactory, SelfReleaser> Fact = std::move(MaybeFactory.right());

		Steinberg::PFactoryInfo LoadedFactoryInfo;
		Fact->getFactoryInfo(&LoadedFactoryInfo);

		std::vector<FVST3ClassInfo> Classes;

		for (int Index = 0; Index < Fact->countClasses(); ++Index)
		{
			if (maybe_vstma_unique_ptr<Steinberg::IPluginFactory3> F3
				= queryInterface<Steinberg::IPluginFactory3>(Fact))
			{
				Steinberg::PClassInfoW Info;
				F3.right()->getClassInfoUnicode(Index, &Info);
				Classes.emplace_back(Info);
			}
			else if (maybe_vstma_unique_ptr<Steinberg::IPluginFactory2> F2
				= queryInterface<Steinberg::IPluginFactory2>(Fact))
			{
				Steinberg::PClassInfo2 Info;
				F2.right()->getClassInfo2(Index, &Info);
				Classes.emplace_back(Info);
			}
			else
			{
				Steinberg::PClassInfo Info;
				Fact->getClassInfo(Index, &Info);
				Classes.emplace_back(Info);
			}
		}

		this->Module = std::move(Mod);
		this->Factory = std::move(Fact);
		this->FactoryInfo = FFactoryInfo(LoadedFactoryInfo);
		this->ClassInfoList = std::move(Classes);
	}

	const FFactoryInfo& GetFactoryInfo() const
	{
		return FactoryInfo;
	}

	size_t GetComponentCount() const
	{
		return ClassInfoList.size();
	}

	const FVST3ClassInfo& GetComponentInfo(size_t Index)
	{
		return ClassInfoList[Index];
	}

private:
	std::shared_ptr<VST3::Hosting::Module> Module;
	std::unique_ptr<Steinberg::IPluginFactory, SelfReleaser> Factory;
	FFactoryInfo FactoryInfo;
	std::vector<FVST3ClassInfo> ClassInfoList;
};

FVST3PluginFactory::FVST3PluginFactory(const FString& ModulePath)
{
	PImpl = MakeUnique<FImpl>(ModulePath);
}

FVST3PluginFactory::~FVST3PluginFactory()
{
}

const FFactoryInfo& FVST3PluginFactory::GetFactoryInfo() const
{
	return PImpl->GetFactoryInfo();
}

size_t FVST3PluginFactory::GetComponentCount() const
{
	return PImpl->GetComponentCount();
}

const FVST3ClassInfo& FVST3PluginFactory::GetComponentInfo(size_t Index) const
{
	return PImpl->GetComponentInfo(Index);
}

TUniquePtr<UVST3Plugin> FVST3PluginFactory::CreateByIndex(size_t Index)
{
	return nullptr;	
}

TUniquePtr<UVST3Plugin> FVST3PluginFactory::CreateByID(const FVST3ClassInfo::FCID& ComponentId)
{
	return nullptr;	
}

uint32 FVST3PluginFactory::GetNumLoadedPlugins() const
{
	return 0;
}

FFactoryInfo::FFactoryInfo(): Flags(0)
{
}

FFactoryInfo::FFactoryInfo(Steinberg::PFactoryInfo const& info):
	Vendor(WCHAR_TO_TCHAR(info.vendor)),
	Url(WCHAR_TO_TCHAR(info.url)),
	Email(WCHAR_TO_TCHAR(info.email)),
	Flags(info.flags)
{
}

bool FFactoryInfo::IsDiscardable() const
{
	return (Flags & Steinberg::PFactoryInfo::FactoryFlags::kClassesDiscardable) != 0;
}

bool FFactoryInfo::IsLicenseCheck() const
{
	return (Flags & Steinberg::PFactoryInfo::FactoryFlags::kClassesDiscardable) != 0;
}

bool FFactoryInfo::IsComponentNonDiscardable() const
{
	return (Flags & Steinberg::PFactoryInfo::FactoryFlags::kComponentNonDiscardable) != 0;
}

bool FFactoryInfo::IsUnicode() const
{
	return (Flags & Steinberg::PFactoryInfo::FactoryFlags::kUnicode) != 0;
}

FString FFactoryInfo::GetVendor() const
{
	return Vendor;
}

FString FFactoryInfo::GetURL() const
{
	return Url;
}

FString FFactoryInfo::GetEmail() const
{
	return Email;
}
