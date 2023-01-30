#include "VST3ModuleHandle.h"

namespace VST3Plugin::Delegates::Private
{
	TAtomic<uint64> GNextID(1);
}

FVST3ModuleHandle::FVST3ModuleHandle(): ID(0)
{
}

FVST3ModuleHandle FVST3ModuleHandle::NewHandle()
{
	return FVST3ModuleHandle(GenerateNewHandle);
}

FVST3ModuleHandle::FVST3ModuleHandle(EGenerateNewHandleType): ID(GeneratedNewID())
{
}

bool FVST3ModuleHandle::IsValid() const
{
	return ID != 0;
}

uint64 FVST3ModuleHandle::GeneratedNewID()
{
	using namespace VST3Plugin::Delegates::Private;

	uint64 Result = ++GNextID;

	if (Result == 0)
	{
		Result = ++GNextID;
	}

	return Result;
}

bool operator==(const FVST3ModuleHandle& Lhs, const FVST3ModuleHandle& Rhs)
{
	return Lhs.ID == Rhs.ID;
}

bool operator!=(const FVST3ModuleHandle& Lhs, const FVST3ModuleHandle& Rhs)
{
	return Lhs.ID != Rhs.ID;
}

FVST3ModuleHandle::operator bool() const
{
	return IsValid();
}

uint32 GetTypeHash(const FVST3ModuleHandle& Key)
{
	return GetTypeHash(Key.ID);
}
