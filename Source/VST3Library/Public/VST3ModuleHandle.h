#pragma once

#include "CoreMinimal.h"
#include "VST3ModuleHandle.generated.h"

USTRUCT(BlueprintType)
struct FVST3ModuleHandle
{
	GENERATED_BODY()
	
	enum EGenerateNewHandleType
	{
		GenerateNewHandle
	};

	FVST3ModuleHandle();

	static FVST3ModuleHandle NewHandle();

	bool IsValid() const;

private:
	explicit FVST3ModuleHandle(EGenerateNewHandleType);

	friend bool operator==(const FVST3ModuleHandle& Lhs, const FVST3ModuleHandle& Rhs);

	friend bool operator!=(const FVST3ModuleHandle& Lhs, const FVST3ModuleHandle& Rhs);

	explicit operator bool() const;

	friend FORCEINLINE uint32 GetTypeHash(const FVST3ModuleHandle& Key);

	static uint64 GeneratedNewID();

	uint64 ID;
};
