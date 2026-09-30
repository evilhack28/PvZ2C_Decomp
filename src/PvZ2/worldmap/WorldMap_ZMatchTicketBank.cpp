//
//  WorldMap_ZMatchTicketBank.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "WorldMap_ZMatchTicketBank.h"

void WorldMap_ZMatchTicketBank::initLoadingResourcesGroupList()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(WorldMap_ZMatchTicketBank);

void WorldMap_ZMatchTicketBank::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(WorldMap_ZMatchTicketBank);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ZMatchTicketBank);

	REFLECTION_CLASSBUILDER_END(WorldMap_ZMatchTicketBank);
}
