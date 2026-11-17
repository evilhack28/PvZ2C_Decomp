//
//  PlantWarsEndOfPlayData.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-11-17.
//

#include "SexyAppFramework/Common.h"

#include "PlantWars.h"
#include "ReflectionBuilder.h"

/////////////// Lifecycle ///////////////

PlantWarsEndOfPlayData::PlantWarsEndOfPlayData()
{
}

PlantWarsEndOfPlayData::PlantWarsEndOfPlayData(const PlantWarsEndOfPlayData& i_other) = default;

PlantWarsEndOfPlayData& PlantWarsEndOfPlayData::operator=(const PlantWarsEndOfPlayData& i_other) = default;

/////////////// Reflection ///////////////

RT_CLASS_IMPLEMENT(PlantWarsEndOfPlayData);

void PlantWarsEndOfPlayData::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantWarsEndOfPlayData);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(INetworkData);

		REFLECTION_CLASSBUILDER_FIELD(int, starNum);
		REFLECTION_CLASSBUILDER_FIELD(bool, isPass);
		REFLECTION_CLASSBUILDER_FIELD(std::vector<int>, score);
		REFLECTION_CLASSBUILDER_FIELD(std::vector<S2C_BonusInfo>, reward);
	REFLECTION_CLASSBUILDER_END(PlantWarsEndOfPlayData);
}
