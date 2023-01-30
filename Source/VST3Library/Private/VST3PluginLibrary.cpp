// Fill out your copyright notice in the Description page of Project Settings.


#include "VST3PluginLibrary.h"

#include "VST3Library.h"

FVST3ModuleHandle UVST3PluginLibrary::LoadVST3Module(const FString& Path)
{
	if (const auto [Handle, Factory] = FVST3LibraryModule::Get().FindOrCreatePluginFactory(Path);
		Handle.IsValid() && Factory.IsValid())
	{
		// for (size_t Idx = 0; Idx < Factory->GetComponentCount(); Idx++)
		// {
		// 	FVST3ClassInfo Info = Factory->GetComponentInfo(Idx);
		//
		// 	UE_LOG(LogVST3Library, Log, TEXT("Name: %s"), *Info.GetName());
		// 	UE_LOG(LogVST3Library, Log, TEXT("Category: %s"), *Info.GetCategory());
		// 	if (Info.HasClassInfo2())
		// 	{
		// 		FVST3ClassInfoV2 Info2 = Info.GetClassInfo2();
		// 		UE_LOG(LogVST3Library, Log, TEXT("SubCategories: %s"), *Info2.GetSubCategories());
		// 		UE_LOG(LogVST3Library, Log, TEXT("Vendor: %s"), *Info2.GetVendor());
		// 		UE_LOG(LogVST3Library, Log, TEXT("Version: %s"), *Info2.GetVersion());
		// 		UE_LOG(LogVST3Library, Log, TEXT("VST Version: %s"), *Info2.GetSDKVersion());
		// 	}
		// 	UE_LOG(LogVST3Library, Log, TEXT("IsEffect: %d"), Info.IsEffect());
		// 	UE_LOG(LogVST3Library, Log, TEXT("IsInstrument: %d"), Info.IsInstrument());
		// }
		return Handle;
	}
	return FVST3ModuleHandle();
}

TArray<FVST3ClassInfo> UVST3PluginLibrary::GetModuleInfoList(const FVST3ModuleHandle& InHandle)
{
	TArray<FVST3ClassInfo> Infos;
	if (const FVST3PluginFactoryPtr Factory = FVST3LibraryModule::GetModuleFactory(InHandle))
	{
		for (size_t Index = 0; Index < Factory->GetComponentCount(); Index++)
		{
			Infos.Add(Factory->GetComponentInfo(Index));
		}
	}
	return Infos;
}
