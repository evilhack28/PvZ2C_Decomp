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

void SummerFireworksWaveAction::WaveUpdate(int i_arg0, Sexy::MTRand & i_arg1)
{
}

void SummerFireworksWaveAction::WaveEnd(int i_arg0, Sexy::MTRand & i_arg1)
{
}
