//
//  GridItemPlantShield.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "GridItemPlantShield.h"

GridItemPlantShield::GridItemPlantShield()
{
}

GridItemPlantShield::~GridItemPlantShield()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(GridItemPlantShield);

void GridItemPlantShield::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(GridItemPlantShield);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GridItemBreakableTarget);

	REFLECTION_CLASSBUILDER_FIELD(RtWeakPtr<GameObject>, m_owner);

	REFLECTION_CLASSBUILDER_END(GridItemPlantShield);
}
