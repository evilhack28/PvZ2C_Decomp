//
//  S2C_SalesStates.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-11-12.
//

#include "SexyAppFramework/Common.h"

#include "NetworkData.h"
#include "ReflectionBuilder.h"

/////////////// Reflection ///////////////

RT_CLASS_IMPLEMENT(S2C_SalesStates);

void S2C_SalesStates::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(S2C_SalesLevelUpInfo);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(int, levelUp, lu);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(int, plantId, i);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(int, targetLevel, s);
	REFLECTION_CLASSBUILDER_END(S2C_SalesLevelUpInfo);

	REFLECTION_CLASSBUILDER_BEGIN(S2C_SalesStates);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(INetworkData);

		REFLECTION_CLASSBUILDER_FIELD_RENAME(std::vector<S2C_BonusInfo>, m_bonusList, bl);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(S2C_PlayerInfo, m_playerInfo, p);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(S2C_SalesLevelUpInfo, m_levelUpInfo, lvi);
	REFLECTION_CLASSBUILDER_END(S2C_SalesStates);
}
