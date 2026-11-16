//
//  BeghouledWaveProgressMeter.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "BeghouledWaveProgressMeter.h"

void BeghouledWaveProgressMeter::initLoadingResourcesGroupList()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(BeghouledWaveProgressMeter);

void BeghouledWaveProgressMeter::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(BeghouledWaveProgressMeter);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(UIWidget);

		REFLECTION_CLASSBUILDER_FIELD(uint8, m_targetFillPercent);
		REFLECTION_CLASSBUILDER_FIELD(float, m_currentDisplayPercent);
	REFLECTION_CLASSBUILDER_END(BeghouledWaveProgressMeter);
}
