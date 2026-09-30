//
//  WorldMap_CoinBank.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "WorldMap_CoinBank.h"

void WorldMap_CoinBank::initLoadingResourcesGroupList()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(WorldMap_CoinBank);

void WorldMap_CoinBank::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(WorldMap_CoinBank);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(CoinBank);

	REFLECTION_CLASSBUILDER_END(WorldMap_CoinBank);
}
