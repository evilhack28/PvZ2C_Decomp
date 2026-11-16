//
//  GridItemInfinutShieldSegment.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "GridItemInfinutShieldSegment.h"

GridItemInfinutShieldSegment::GridItemInfinutShieldSegment()
{
}

GridItemInfinutShieldSegment::~GridItemInfinutShieldSegment()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(GridItemInfinutShieldSegment);

void GridItemInfinutShieldSegment::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(GridItemInfinutShieldSegment);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GridItemLinkedPlantShield);

	REFLECTION_CLASSBUILDER_FIELD(int, m_currentDamageState);

	REFLECTION_CLASSBUILDER_END(GridItemInfinutShieldSegment);
}
