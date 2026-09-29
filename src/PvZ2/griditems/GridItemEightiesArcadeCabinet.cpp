//
//  GridItemEightiesArcadeCabinet.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "GridItemEightiesArcadeCabinet.h"

GridItemEightiesArcadeCabinet::~GridItemEightiesArcadeCabinet()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(GridItemEightiesArcadeCabinet);

void GridItemEightiesArcadeCabinet::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(GridItemEightiesArcadeCabinet);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GridItemJammable);

		REFLECTION_CLASSBUILDER_FIELD(int, m_state);
		REFLECTION_CLASSBUILDER_FIELD(EntityComponent_GroundEffect, m_groundEffect);
		REFLECTION_CLASSBUILDER_FIELD(float, m_risingTime);
	REFLECTION_CLASSBUILDER_END(GridItemEightiesArcadeCabinet);
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(GridItemEightiesArcadeCabinetProps);

void GridItemEightiesArcadeCabinetProps::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(GridItemEightiesArcadeCabinetProps);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GridItemBreakableTargetProps);

		REFLECTION_CLASSBUILDER_FIELD(std::string, JamStyle);
		REFLECTION_CLASSBUILDER_FIELD(std::vector<BasicZombieWeights>, ZombieTypesToSpawn);
	REFLECTION_CLASSBUILDER_END(GridItemEightiesArcadeCabinetProps);
}
