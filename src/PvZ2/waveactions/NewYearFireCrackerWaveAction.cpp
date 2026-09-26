//
//  NewYearFireCrackerWaveAction.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "NewYearFireCrackerWaveAction.h"

NewYearFireCrackerWaveAction::NewYearFireCrackerWaveAction()
{
}

NewYearFireCrackerWaveAction::~NewYearFireCrackerWaveAction()
{
}

NewYearFireCrackerWaveActionProps::~NewYearFireCrackerWaveActionProps()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(NewYearFireCrackerWaveAction);

void NewYearFireCrackerWaveAction::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(NewYearFireCrackerWaveAction);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(WaveAction);

	REFLECTION_CLASSBUILDER_END(NewYearFireCrackerWaveAction);
}

void NewYearFireCrackerWaveAction::WaveUpdate(int i_arg0, Sexy::MTRand & i_arg1)
{
}

void NewYearFireCrackerWaveAction::WaveEnd(int i_arg0, Sexy::MTRand & i_arg1)
{
}
