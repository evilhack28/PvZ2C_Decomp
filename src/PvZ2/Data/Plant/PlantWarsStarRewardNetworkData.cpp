//
//  PlantWarsStarRewardNetworkData.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-11-17.
//

#include "SexyAppFramework/Common.h"

#include "PlantWars.h"
#include "ReflectionBuilder.h"

/////////////// Reflection ///////////////

RT_CLASS_IMPLEMENT(PlantWarsStarRewardNetworkData);

void PlantWarsStarRewardNetworkData::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantWarsStarRewardNetworkData);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(INetworkData);

		REFLECTION_CLASSBUILDER_FIELD(int, worldId);
		REFLECTION_CLASSBUILDER_FIELD(int, id);
		REFLECTION_CLASSBUILDER_FIELD(std::vector<S2C_BonusInfo>, reward);
	REFLECTION_CLASSBUILDER_END(PlantWarsStarRewardNetworkData);
}
