//
//  SummerFireworksWaveAction.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "SummerFireworksWaveAction.h"

SummerFireworksWaveAction::SummerFireworksWaveAction()
{
}

SummerFireworksWaveAction::~SummerFireworksWaveAction()
{
}

SummerFireworksWaveActionProps::~SummerFireworksWaveActionProps()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(SummerFireworksWaveAction);

void SummerFireworksWaveAction::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(SummerFireworksWaveAction);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(WaveAction);

	REFLECTION_CLASSBUILDER_END(SummerFireworksWaveAction);
}

void SummerFireworksWaveAction::WaveUpdate(int i_waveNumber, Sexy::MTRand & i_random)
{
}

void SummerFireworksWaveAction::WaveEnd(int i_waveNumber, Sexy::MTRand & i_random)
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(SummerFireworksWaveActionProps);

void SummerFireworksWaveActionProps::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(SummerFireworksData);
	REFLECTION_CLASSBUILDER_END(SummerFireworksData);

	REFLECTION_CLASSBUILDER_BEGIN(SummerFireworksWaveActionProps);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(WaveActionProperties);

		REFLECTION_CLASSBUILDER_FIELD(std::vector<SummerFireworksData>, SummerFireworksGroup);
	REFLECTION_CLASSBUILDER_END(SummerFireworksWaveActionProps);
}
