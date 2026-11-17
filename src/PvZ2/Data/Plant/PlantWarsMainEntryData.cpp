//
//  PlantWarsMainEntryData.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-11-17.
//

#include "SexyAppFramework/Common.h"

#include "PlantWars.h"
#include "ReflectionBuilder.h"

/////////////// Lifecycle ///////////////

PlantWarsMainEntryData::PlantWarsMainEntryData()
{
	cw = "";
	ct = 0;
	offseason = false;
}

PlantWarsMainEntryData& PlantWarsMainEntryData::operator=(const PlantWarsMainEntryData& i_other) = default;

/////////////// Reflection ///////////////

RT_CLASS_IMPLEMENT(PlantWarsMainEntryData);

void PlantWarsMainEntryData::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantWarsLeaderBoardLineData);
		REFLECTION_CLASSBUILDER_FIELD(int, r);
		REFLECTION_CLASSBUILDER_FIELD(int, s);
		REFLECTION_CLASSBUILDER_FIELD(int, h);
		REFLECTION_CLASSBUILDER_FIELD(std::string, pn);
	REFLECTION_CLASSBUILDER_END(PlantWarsLeaderBoardLineData);

	REFLECTION_CLASSBUILDER_BEGIN(PlantWarsStarRewardData);
		REFLECTION_CLASSBUILDER_FIELD(int, id);
		REFLECTION_CLASSBUILDER_FIELD(int, condition);
		REFLECTION_CLASSBUILDER_FIELD(std::vector<S2C_BonusInfo>, reward);
		REFLECTION_CLASSBUILDER_FIELD(bool, status);
	REFLECTION_CLASSBUILDER_END(PlantWarsStarRewardData);

	REFLECTION_CLASSBUILDER_BEGIN(PlantWarsLeaderBoardBonusData);
		REFLECTION_CLASSBUILDER_FIELD(int, ci);
		REFLECTION_CLASSBUILDER_FIELD(std::vector<PlantWarsStarRewardData>, bdl);
	REFLECTION_CLASSBUILDER_END(PlantWarsLeaderBoardBonusData);

	REFLECTION_CLASSBUILDER_BEGIN(PlantWarsLeaderBoardData);
		REFLECTION_CLASSBUILDER_FIELD(int, s);
		REFLECTION_CLASSBUILDER_FIELD(int, r);
		REFLECTION_CLASSBUILDER_FIELD(std::vector<PlantWarsLeaderBoardLineData>, rl);
	REFLECTION_CLASSBUILDER_END(PlantWarsLeaderBoardData);

	REFLECTION_CLASSBUILDER_BEGIN(PlantWarsStarInfoData);
		REFLECTION_CLASSBUILDER_FIELD(bool, isCompleted);
		REFLECTION_CLASSBUILDER_FIELD(int, score);
	REFLECTION_CLASSBUILDER_END(PlantWarsStarInfoData);

	REFLECTION_CLASSBUILDER_BEGIN(PlantWarsNodeData);
		REFLECTION_CLASSBUILDER_FIELD(std::vector<std::string>, battleArray);
		REFLECTION_CLASSBUILDER_FIELD(int, score);
		REFLECTION_CLASSBUILDER_FIELD(int, curScore);
		REFLECTION_CLASSBUILDER_FIELD(pvztime_t, lt);
	REFLECTION_CLASSBUILDER_END(PlantWarsNodeData);

	REFLECTION_CLASSBUILDER_BEGIN(PlantWarsLevelData);
		REFLECTION_CLASSBUILDER_FIELD(std::vector<S2C_BonusInfo>, firstReward);
		REFLECTION_CLASSBUILDER_FIELD(std::vector<S2C_BonusInfo>, reward);
		REFLECTION_CLASSBUILDER_FIELD(std::vector<PlantWarsStarInfoData>, starsTarget);
		REFLECTION_CLASSBUILDER_FIELD(std::vector<PlantWarsNodeData>, nodes);
		REFLECTION_CLASSBUILDER_FIELD(int, score);
		REFLECTION_CLASSBUILDER_FIELD(int, s);
		REFLECTION_CLASSBUILDER_FIELD(PlantWarsStarInfoData, passTarget);
		REFLECTION_CLASSBUILDER_FIELD(int, ls);
	REFLECTION_CLASSBUILDER_END(PlantWarsLevelData);

	REFLECTION_CLASSBUILDER_BEGIN(PlantWarsWorldData);
		REFLECTION_CLASSBUILDER_FIELD(std::string, pw);
		REFLECTION_CLASSBUILDER_FIELD(int, id);
		REFLECTION_CLASSBUILDER_FIELD(PlantWarsLeaderBoardBonusData, lbb);
		REFLECTION_CLASSBUILDER_FIELD(PlantWarsLeaderBoardData, lb);
		REFLECTION_CLASSBUILDER_FIELD(int, starCnt);
		REFLECTION_CLASSBUILDER_FIELD(std::vector<PlantWarsLevelData>, levels);
		REFLECTION_CLASSBUILDER_FIELD(std::vector<PlantWarsStarRewardData>, reward);
		REFLECTION_CLASSBUILDER_FIELD(std::vector<int>, ppc);
	REFLECTION_CLASSBUILDER_END(PlantWarsWorldData);

	REFLECTION_CLASSBUILDER_BEGIN(PlantWarsMainEntryData);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_FIELD(int, uniId);
		REFLECTION_CLASSBUILDER_FIELD(int, ct);
		REFLECTION_CLASSBUILDER_FIELD(bool, offseason);
		REFLECTION_CLASSBUILDER_FIELD(std::string, cw);
		REFLECTION_CLASSBUILDER_FIELD(std::vector<PlantWarsWorldData>, worldInfo);
	REFLECTION_CLASSBUILDER_END(PlantWarsMainEntryData);
}
