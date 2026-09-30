//
//  PoolDaylightStage.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "PoolDaylightStage.h"

PoolDaylightStage::~PoolDaylightStage()
{
}

PoolDaylightStageProperties::~PoolDaylightStageProperties()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PoolDaylightStage);

void PoolDaylightStage::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PoolDaylightStage);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(StageModule);

		REFLECTION_CLASSBUILDER_FIELD(std::vector<int32>, m_planks);
	REFLECTION_CLASSBUILDER_END(PoolDaylightStage);
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PoolDaylightStageProperties);

void PoolDaylightStageProperties::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PoolDaylightStageProperties);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(StageModuleProperties);

	REFLECTION_CLASSBUILDER_END(PoolDaylightStageProperties);
}

void PoolDaylightStage::onWaterAnimEnd()
{
}

void PoolDaylightStage::showToxicWater()
{
}

int PoolDaylightStage::GetPlankStartGridColumn() const
{
	return 5;
}
