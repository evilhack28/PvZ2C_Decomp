//
//  GridItemPlantCrackerFlower.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "Plant_Cracker.h"

GridItemPlantCrackerFlower::~GridItemPlantCrackerFlower()
{
}

GridItemPlantCrackerFlowerProps::~GridItemPlantCrackerFlowerProps()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(GridItemPlantCrackerFlower);

void GridItemPlantCrackerFlower::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(GridItemPlantCrackerFlower);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GridItemAnimation);

		REFLECTION_CLASSBUILDER_FIELD(int, m_state);
	REFLECTION_CLASSBUILDER_END(GridItemPlantCrackerFlower);
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(GridItemPlantCrackerFlowerProps);

void GridItemPlantCrackerFlowerProps::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(GridItemPlantCrackerFlowerProps);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GridItemAnimationProps);

		REFLECTION_CLASSBUILDER_FIELD(SexyVector2, PopAnimRenderOffset);
		REFLECTION_CLASSBUILDER_FIELD(pvztime_t, Lifetime);
	REFLECTION_CLASSBUILDER_END(GridItemPlantCrackerFlowerProps);
}
