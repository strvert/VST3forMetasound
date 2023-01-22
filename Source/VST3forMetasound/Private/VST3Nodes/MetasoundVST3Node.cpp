#include <fstream>

#include "MetasoundAudioBuffer.h"
#include "MetasoundBuilderInterface.h"
#include "MetasoundExecutableOperator.h"
#include "MetasoundNodeInterface.h"
#include "MetasoundDataReference.h"
#include "MetasoundFacade.h"
#include "MetasoundNodeRegistrationMacro.h"
#include "MetasoundParamHelper.h"
#include "MetasoundPrimitives.h"
#include "MetasoundStandardNodesCategories.h"
#include "VST3forMetasound.h"
#include "VST3Library.h"
#include "VST3PluginAsset.h"

#define LOCTEXT_NAMESPACE "FVST3InstrumentSourceNode"

namespace Metasound
{
	using MIDINoteValueType = int32;

	namespace VST3InstrumentSourceNodeNames
	{
		METASOUND_PARAM(TriggerAttack, "Attack", "Trigger attack");
		METASOUND_PARAM(TriggerRelease, "Release", "Trigger release");
		METASOUND_PARAM(VST3Plugin, "VST3Plugin", "VST3 Plugin");
		METASOUND_PARAM(MidiNote, "MidiNote", "Instrument Plugin に入力する MIDI Note Number");
		METASOUND_PARAM(Audio, "Audio", "Instrument Plugin の出力オーディオ");
	}

	class FVST3InstrumentSourceOperator : public TExecutableOperator<FVST3InstrumentSourceOperator>
	{
	public:
		FVST3InstrumentSourceOperator(const FOperatorSettings& InSettings,
		                              const FTriggerReadRef& InTriggerAttack,
		                              const FTriggerReadRef& InTriggerRelease,
		                              const FVST3PluginAssetReadRef& InVST3Plugin,
		                              const TDataReadReference<MIDINoteValueType>& InMidiNote);

		void Execute()
		{
			if (bWritten)
			{
				FMemory::Memzero(AudioBuffer->GetData(), sizeof(float) * AudioBuffer->Num());
				bWritten = false;
			}

			const auto GetLastIndex = [this](const FTriggerReadRef& Trigger)
			{
				auto PreTrigger = [](int32, int32)
				{
				};

				auto OnTrigger = [this](int32 StartFrame, int32 EndFrame)
				{
					const FVST3PluginProxyPtr Proxy = VST3PluginRef->GetVST3PluginProxy();
					if (Proxy.IsValid())
					{
					}
				};

				Trigger->ExecuteBlock(PreTrigger, OnTrigger);
			};

			GetLastIndex(TriggerAttackRef);
		}

		static const FNodeClassMetadata& GetNodeInfo()
		{
			auto InitNodeInfo = []() -> FNodeClassMetadata
			{
				const FName OperatorName = "VST3 Instrument Source Node";

				FNodeClassMetadata Info{};
				Info.ClassName = {TEXT("VST3"), OperatorName, FName()};
				Info.MajorVersion = 1;
				Info.MinorVersion = 0;
				Info.DisplayName = METASOUND_LOCTEXT("VST3InstrumentSourceNodeDisplayName",
				                                     "VST3 Instrument Source Node");
				Info.Description = METASOUND_LOCTEXT("", "");
				Info.Author = PluginAuthor;
				Info.PromptIfMissing = PluginNodeMissingPrompt;
				Info.DefaultInterface = DeclareVertexInterface();
				Info.CategoryHierarchy.Emplace(NodeCategories::Generators);

				return Info;
			};

			static const FNodeClassMetadata Info = InitNodeInfo();
			return Info;
		}

		static const FVertexInterface& DeclareVertexInterface()
		{
			using namespace VST3InstrumentSourceNodeNames;

			static const FVertexInterface Interface(
				FInputVertexInterface(
					TInputDataVertex<FTrigger>(METASOUND_GET_PARAM_NAME_AND_METADATA(TriggerAttack)),
					TInputDataVertex<FTrigger>(METASOUND_GET_PARAM_NAME_AND_METADATA(TriggerRelease)),
					TInputDataVertex<FVST3PluginAsset>(METASOUND_GET_PARAM_NAME_AND_METADATA(VST3Plugin)),
					TInputDataVertex<MIDINoteValueType>(METASOUND_GET_PARAM_NAME_AND_METADATA(MidiNote))
				),
				FOutputVertexInterface(
					TOutputDataVertex<FAudioBuffer>(METASOUND_GET_PARAM_NAME_AND_METADATA(Audio))
				)
			);

			return Interface;
		}

		virtual FDataReferenceCollection GetInputs() const override;
		virtual FDataReferenceCollection GetOutputs() const override;

		static TUniquePtr<IOperator> CreateOperator(const FCreateOperatorParams& InParams, FBuildErrorArray& OutErrors)
		{
			using namespace VST3InstrumentSourceNodeNames;

			const FDataReferenceCollection& InputCollection = InParams.InputDataReferences;
			const FInputVertexInterface& InputInterface = DeclareVertexInterface().GetInputInterface();

			TDataReadReference<MIDINoteValueType> InMidiNote
				= InputCollection.GetDataReadReferenceOrConstructWithVertexDefault<MIDINoteValueType>(
					InputInterface, METASOUND_GET_PARAM_NAME(MidiNote), InParams.OperatorSettings);
			FVST3PluginAssetReadRef InVST3Plugin
				= InputCollection.GetDataReadReferenceOrConstruct<FVST3PluginAsset>(
					METASOUND_GET_PARAM_NAME(VST3Plugin));
			FTriggerReadRef InTriggerAttack
				= InputCollection.GetDataReadReferenceOrConstructWithVertexDefault<FTrigger>(
					InputInterface, METASOUND_GET_PARAM_NAME(TriggerAttack), InParams.OperatorSettings);
			FTriggerReadRef InTriggerRelease
				= InputCollection.GetDataReadReferenceOrConstructWithVertexDefault<FTrigger>(
					InputInterface, METASOUND_GET_PARAM_NAME(TriggerRelease), InParams.OperatorSettings);

			return MakeUnique<FVST3InstrumentSourceOperator>(InParams.OperatorSettings, InTriggerAttack,
			                                                 InTriggerRelease, InVST3Plugin, InMidiNote);
		}

	private:
		FTriggerReadRef TriggerAttackRef;
		FTriggerReadRef TriggerReleaseRef;
		FVST3PluginAssetReadRef VST3PluginRef;
		TDataReadReference<MIDINoteValueType> MidiNote;

		FAudioBufferWriteRef AudioBuffer;

		float Phase = 0.0;
		float SampleRate;
		bool bWritten;
	};

	FVST3InstrumentSourceOperator::FVST3InstrumentSourceOperator(
		const FOperatorSettings& InSettings, const FTriggerReadRef& InTriggerAttack,
		const FTriggerReadRef& InTriggerRelease, const FVST3PluginAssetReadRef& InVST3Plugin,
		const TDataReadReference<MIDINoteValueType>& InMidiNote)
		: TriggerAttackRef(InTriggerAttack), TriggerReleaseRef(InTriggerRelease), VST3PluginRef(InVST3Plugin),
		  MidiNote(InMidiNote), AudioBuffer(FAudioBufferWriteRef::CreateNew(InSettings)),
		  SampleRate(InSettings.GetSampleRate()),
		  bWritten(true)
	{
	}

	FDataReferenceCollection FVST3InstrumentSourceOperator::GetInputs() const
	{
		using namespace VST3InstrumentSourceNodeNames;
		FDataReferenceCollection Collection;
		Collection.AddDataReadReference(METASOUND_GET_PARAM_NAME(MidiNote), MidiNote);
		return Collection;
	}

	FDataReferenceCollection FVST3InstrumentSourceOperator::GetOutputs() const
	{
		using namespace VST3InstrumentSourceNodeNames;
		FDataReferenceCollection Collection;
		Collection.AddDataReadReference(METASOUND_GET_PARAM_NAME(Audio), AudioBuffer);
		return Collection;
	}

	class FVST3InstrumentSourceNode : public FNodeFacade
	{
	public:
		FVST3InstrumentSourceNode(const FNodeInitData& InitData)
			: FNodeFacade(InitData.InstanceName, InitData.InstanceID,
			              TFacadeOperatorClass<FVST3InstrumentSourceOperator>())
		{
		}

		virtual ~FVST3InstrumentSourceNode() = default;
	};

	METASOUND_REGISTER_NODE(FVST3InstrumentSourceNode);
}

#undef LOCTEXT_NAMESPACE
