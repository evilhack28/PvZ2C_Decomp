//
//  BossProgressMeterRift.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "BossProgressMeterRift.h"

BossProgressMeterRift::~BossProgressMeterRift()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(BossProgressMeterRift);

void BossProgressMeterRift::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(BossProgressMeterRift);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(BossProgressMeter);

	REFLECTION_CLASSBUILDER_FIELD(bool, m_lootPhaseActive);

	REFLECTION_CLASSBUILDER_END(BossProgressMeterRift);
}

void BossProgressMeterRift::initLoadingResourcesGroupList()
{
}

BossProgressMeterRift::BossProgressMeterRift()
{
	m_lootPhaseActive = 0;
}
