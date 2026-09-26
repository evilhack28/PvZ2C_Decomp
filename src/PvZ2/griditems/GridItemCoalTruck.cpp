//
//  GridItemCoalTruck.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "ZombieSteamCoalMiner.h"

GridItemCoalTruck::GridItemCoalTruck()
{
}

GridItemCoalTruck::~GridItemCoalTruck()
{
}

GridItemCoalTruckProps::GridItemCoalTruckProps()
{
}

GridItemCoalTruckProps::~GridItemCoalTruckProps()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(GridItemCoalTruck);

void GridItemCoalTruck::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(GridItemCoalTruck);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GridItemGravestone);

	REFLECTION_CLASSBUILDER_FIELD(bool, m_hasPlayDieAnim);

	REFLECTION_CLASSBUILDER_END(GridItemCoalTruck);
}
