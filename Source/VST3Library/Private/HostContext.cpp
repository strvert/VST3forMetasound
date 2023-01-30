#include "VST3Plugin.h"
#include "base/source/fobject.h"
#include "pluginterfaces/vst/ivsthostapplication.h"

class UVST3Plugin::FHostContext::FImpl : public Steinberg::FObject, public Steinberg::Vst::IHostApplication
{
public:
	OBJ_METHODS(FHostContext::FImpl, FObject)
	REFCOUNT_METHODS(FObject)
	
	DEFINE_INTERFACES
	DEF_INTERFACE(FObject)
	DEF_INTERFACE(Steinberg::Vst::IHostApplication)
	END_DEFINE_INTERFACES(FObject)

	FImpl(const FString& InHostName):
		HostName(InHostName)
	{
	}

	virtual ~FImpl() = default;

	FString HostName;

protected:
	virtual Steinberg::tresult getName(Steinberg::Vst::String128 name) override;
	virtual Steinberg::tresult createInstance(Steinberg::TUID cid, Steinberg::TUID _iid, void** obj) override;
};

Steinberg::tresult UVST3Plugin::FHostContext::FImpl::getName(Steinberg::Vst::String128 name)
{
	return {};
}

Steinberg::tresult UVST3Plugin::FHostContext::FImpl::createInstance(Steinberg::TUID cid, Steinberg::TUID _iid, void** obj)
{
	return {};
}

UVST3Plugin::FHostContext::FHostContext(const FString& HostName)
{
	PImpl = MakeUnique<FImpl>(HostName);
}

UVST3Plugin::FHostContext::~FHostContext()
{
}

Steinberg::Vst::IHostApplication* UVST3Plugin::FHostContext::GetHostPtr() const
{
	return PImpl.Get();
}
