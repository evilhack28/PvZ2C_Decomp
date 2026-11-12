//
//  S2C_ExplorerStart.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-11-12.
//

#include "SexyAppFramework/Common.h"

#include "NetworkData.h"
#include "ReflectionBuilder.h"

/////////////// Reflection ///////////////

RT_CLASS_IMPLEMENT(S2C_ExplorerStart);

void S2C_ExplorerStart::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(S2C_Explore_Team);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(uint32, exploreEndTime, aet);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(int32, dungeonId, wi);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(int, chances, c);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(int, status, s);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(int, plantChipId, pci);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(int, bonus, b);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(int, surpriseObjectId, soi);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(int, surprise, s1);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(int, coins, g);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(int, surprisePrice, sc);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(std::vector<int>, plantsList, pl);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(int, bonusItem, mc);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(int, addChanceCount, dc);
	REFLECTION_CLASSBUILDER_END(S2C_Explore_Team);

	REFLECTION_CLASSBUILDER_BEGIN(S2C_ExplorerStart);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(INetworkData);

		REFLECTION_CLASSBUILDER_FIELD_RENAME(int, needGems, nc);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(int, gemCost, g);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(std::vector<S2C_Explore_Team>, m_teamList, e);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(S2C_PlayerInfo, m_playerInfo, p);
	REFLECTION_CLASSBUILDER_END(S2C_ExplorerStart);

}
