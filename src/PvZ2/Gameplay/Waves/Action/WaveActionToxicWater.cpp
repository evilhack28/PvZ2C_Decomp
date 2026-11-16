//
//  WaveActionToxicWater.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "WaveActionToxicWater.h"

WaveActionToxicWater::WaveActionToxicWater()
{
}

WaveActionToxicWater::~WaveActionToxicWater()
{
}

WaveActionToxicWaterProps::~WaveActionToxicWaterProps()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(WaveActionToxicWater);

void WaveActionToxicWater::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(WaveActionToxicWater);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(WaveAction);

	REFLECTION_CLASSBUILDER_END(WaveActionToxicWater);
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(WaveActionToxicWaterProps);

void WaveActionToxicWaterProps::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(WaveActionToxicWaterProps);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(WaveActionProperties);

		REFLECTION_CLASSBUILDER_FIELD(float, Damage);
		REFLECTION_CLASSBUILDER_FIELD(int, WaveNum);
	REFLECTION_CLASSBUILDER_END(WaveActionToxicWaterProps);
}

void WaveActionToxicWater::WaveUpdate(int i_waveNumber, Sexy::MTRand & i_random)
{
}

void WaveActionToxicWater::WaveEnd(int i_waveNumber, Sexy::MTRand & i_random)
{
}
