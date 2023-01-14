#include "MetasoundAudioBuffer.h"
#include "MetasoundBuilderInterface.h"
#include "MetasoundExecutableOperator.h"
#include "MetasoundNodeInterface.h"
#include "MetasoundDataReference.h"
#include "MetasoundFacade.h"
#include "MetasoundNodeRegistrationMacro.h"
#include "MetasoundPrimitives.h"
#include "MetasoundParamHelper.h"
#include "MetasoundStandardNodesCategories.h"
#include "MetasoundStandardNodesNames.h"

#define LOCTEXT_NAMESPACE "FVST3InstrumentSourceNode"

namespace Metasound
{
	using MIDINoteValueType = int32;

	namespace VST3InstrumentSourceNodeNames
	{
		METASOUND_PARAM(MidiNote, "MidiNote", "Instrument Plugin に入力する MIDI Note Number");
		METASOUND_PARAM(Audio, "Audio", "Instrument Plugin の出力オーディオ");
	}

	class FVST3InstrumentSourceOperator : public TExecutableOperator<FVST3InstrumentSourceOperator>
	{
	public:
		FVST3InstrumentSourceOperator(const FOperatorSettings& InSettings,
		                              const TDataReadReference<MIDINoteValueType>& InMidiNote);

		void Execute()
		{
			const float OneOverSampleRate = 1.0f / SampleRate;
			constexpr float Frequency = 440.0f;
			const float DeltaPhase = Frequency * OneOverSampleRate;

			static constexpr float TwoPi = 2.f * PI;
			float* OutputBuffer = AudioBuffer->GetData();
			const int32 NumSampleIndex = AudioBuffer->Num();

			for (int32 Index = 0; Index < NumSampleIndex; Index++)
			{
				OutputBuffer[Index] = FMath::Sin(Phase * TwoPi);
				Phase += DeltaPhase;
			}

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

			return MakeUnique<FVST3InstrumentSourceOperator>(InParams.OperatorSettings, InMidiNote);
		}

	private:
		TDataReadReference<MIDINoteValueType> MidiNote;

		FAudioBufferWriteRef AudioBuffer;

		float Phase = 0.0;
		float SampleRate;
	};

	FVST3InstrumentSourceOperator::FVST3InstrumentSourceOperator(
		const FOperatorSettings& InSettings, const TDataReadReference<MIDINoteValueType>& InMidiNote)
		: MidiNote(InMidiNote), AudioBuffer(FAudioBufferWriteRef::CreateNew(InSettings)),
		  SampleRate(InSettings.GetSampleRate())
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
