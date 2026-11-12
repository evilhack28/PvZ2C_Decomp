//
//  S2C_PVP_Login.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-11-12.
//

#include "SexyAppFramework/Common.h"

#include "NetworkData.h"
#include "ReflectionBuilder.h"

/////////////// Reflection ///////////////

RT_CLASS_IMPLEMENT(S2C_PVP_Login);

void S2C_PVP_Login::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(S2C_PVP_Login);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(INetworkData);

		REFLECTION_CLASSBUILDER_FIELD_RENAME(int32, m_remainChallenge, rd);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(int32, m_coldTime, rt);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(int32, m_pvpCup, pc);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(int32, m_pvpCoin, ag);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(int32, m_pvpMedal, am);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(int32, m_gemToday, g);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(int32, m_achievementTrainCoin, tg);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(int32, m_achievementTrainSpace, tc);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(int32, m_leagueId, li);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(uint64, m_maxBattleID, mhi);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(int32, m_trainingSeconds, zplt);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(int32, m_labSeconds, lplt);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(int32, m_baseLevel, bl);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(PvPRankMonthReward, m_rankMonthReward, mrc);
	REFLECTION_CLASSBUILDER_END(S2C_PVP_Login);
}
