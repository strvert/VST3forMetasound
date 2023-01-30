#include "VST3Plugin.h"
#include <pluginterfaces/base/ipluginbase.h>
#include <pluginterfaces/vst/ivstcomponent.h>
#include "pluginterfaces/vst/ivsthostapplication.h"
#include <pluginterfaces/vst/ivsteditcontroller.h>
#include <pluginterfaces/vst/ivstaudioprocessor.h>
#include <pluginterfaces/vst/ivstunits.h>

#include "VST3Library.h"
#include "VST3MAUtils.h"
#include "VST3PluginFactory.h"
#include "Interfaces/IPluginManager.h"

class UVST3Plugin::FImpl
{
public:
	explicit FImpl(Steinberg::IPluginFactory* InFactory, const FVST3ClassInfo& InClassInfo,
	               FHostContext& InContext):
		ClassInfo(InClassInfo), FactoryInfo(), bSingleComponent(false), BlockSize(2048),
		SamplingRate(44100), Status(EStatus::Invalid)
	{
		Steinberg::PFactoryInfo Fi;
		InFactory->getFactoryInfo(&Fi);
		FactoryInfo = FFactoryInfo(Fi);
		LoadInterfaces(InFactory, InClassInfo, InContext);
	}

	void LoadInterfaces(Steinberg::IPluginFactory* InFactory, const FVST3ClassInfo& Info,
	                    FHostContext& InContext)
	{
		using namespace Steinberg;

		const FUID Cid = FUID::fromTUID(Info.GetCID().Data.data());
		maybe_vstma_unique_ptr<Vst::IComponent> NewComponent = createInstance<Vst::IComponent>(InFactory, Cid);

		NewComponent.right()->setIoMode(Vst::IoModes::kAdvanced);
		NewComponent.right()->initialize(InContext.GetHostPtr());;

		maybe_vstma_unique_ptr<Vst::IEditController> EditController
			= queryInterface<Vst::IEditController>(NewComponent.right());
		if (EditController)
		{
			bSingleComponent = true;
		}
		else
		{
			TUID ControllerId;
			EditController = NewComponent.right()->getControllerClassId(ControllerId);
		}

		check(EditController.is_right());

		if (!bSingleComponent)
		{
			EditController.right()->initialize(InContext.GetHostPtr());
		}

		maybe_vstma_unique_ptr<Vst::IComponentHandler> ComponentHandler
			= queryInterface<Vst::IComponentHandler>(InContext.GetHostPtr());
		EditController.right()->setComponentHandler(ComponentHandler.right().get());
		maybe_vstma_unique_ptr<Vst::IAudioProcessor> AudioProcessor
			= queryInterface<Vst::IAudioProcessor>(
				NewComponent.right());
		maybe_vstma_unique_ptr<Vst::IEditController2> EditController2
			= queryInterface<Vst::IEditController2>(EditController.right());

		maybe_vstma_unique_ptr<Vst::IMidiMapping> MidiMapping
			= queryInterface<Vst::IMidiMapping>(EditController.right());
		maybe_vstma_unique_ptr<Vst::IUnitInfo> UnitInfo
			= queryInterface<Vst::IUnitInfo>(EditController.right());

		this->Component = std::move(NewComponent.right());
	}

	enum class EStatus
	{
		Invalid,
		Created,
		Initialized,
		SetupDone,
		Activated,
		Processing,
	};

	const FVST3ClassInfo& ClassInfo;
	FFactoryInfo FactoryInfo;
	bool bSingleComponent;
	uint32 BlockSize;
	uint32 SamplingRate;
	EStatus Status;
	std::unique_ptr<Steinberg::Vst::IComponent, SelfReleaser> Component;
};

UVST3Plugin* UVST3Plugin::LoadPlugin(Steinberg::IPluginFactory* Factory, const FVST3ClassInfo& ClassInfo)
{
	UVST3Plugin* Plugin = NewObject<UVST3Plugin>();
	Plugin->Context = MakeUnique<FHostContext>(FVST3LibraryModule::GetVST3HostName());
	Plugin->PImpl = MakeUnique<FImpl>(Factory, ClassInfo, *Plugin->Context);
	return Plugin;
}

UVST3Plugin::~UVST3Plugin()
{
	PImpl.Reset();
}

UVST3Plugin::FOnPluginDestruction& UVST3Plugin::GetOnPluginDestruction()
{
	return OnPluginDestruction;
}
