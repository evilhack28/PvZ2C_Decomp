//
//  GridItemBackpack.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "ZombieLostCityImpPorter.h"

GridItemBackpack::GridItemBackpack()
{
}

GridItemBackpack::~GridItemBackpack()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(GridItemBackpack);

void GridItemBackpack::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(GridItemBackpack);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GridItemGravestone);

		REFLECTION_CLASSBUILDER_FIELD(bool, m_hasPlayedDeathAnim);
		REFLECTION_CLASSBUILDER_FIELD(float, m_bounceStartTime);
	REFLECTION_CLASSBUILDER_END(GridItemBackpack);
}

PlantingReason GridItemBackpack::GetCantPlantReason() const
{
	return (PlantingReason)26;
}
