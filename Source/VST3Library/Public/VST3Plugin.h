// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <pluginterfaces/vst/ivsthostapplication.h>

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "VST3Plugin.generated.h"

namespace Steinberg
{
	class IPluginFactory;
}

struct FVST3ClassInfo;

UCLASS()
class VST3LIBRARY_API UVST3Plugin : public UObject
{
	GENERATED_BODY()

	DECLARE_MULTICAST_DELEGATE_OneParam(FOnPluginDestruction, TWeakObjectPtr<UVST3Plugin>);
public:
	static UVST3Plugin* LoadPlugin(Steinberg::IPluginFactory* Factory, const FVST3ClassInfo& ClassInfo);
	virtual ~UVST3Plugin() override;


	FOnPluginDestruction& GetOnPluginDestruction();

private:
	FOnPluginDestruction OnPluginDestruction;

	class FImpl;
	TUniquePtr<FImpl> PImpl;

public:
	class FHostContext
	{
	public:
		explicit FHostContext(const FString& HostName);
		virtual ~FHostContext();

		Steinberg::Vst::IHostApplication* GetHostPtr() const;

	private:
		class FImpl;
		TUniquePtr<FImpl> PImpl;
	};

private:
	TUniquePtr<FHostContext> Context;
};
