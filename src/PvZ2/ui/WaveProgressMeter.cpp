//
//  WaveProgressMeter.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "WaveProgressMeter.h"

void WaveProgressMeter::initLoadingResourcesGroupList()
{
}

WaveProgressMeter::~WaveProgressMeter()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(WaveProgressMeter);

void WaveProgressMeter::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(WaveProgressMeter);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(UIWidget);

		REFLECTION_CLASSBUILDER_FIELD(float, m_currentDisplayPercent);
		REFLECTION_CLASSBUILDER_FIELD(bool, m_useHeadImage);
		REFLECTION_CLASSBUILDER_FIELD(std::vector<pvztime_t>, m_lerpFlagEndTime);
	REFLECTION_CLASSBUILDER_END(WaveProgressMeter);
}
