//
//  S2C_PVP_PlayerInfos.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-11-12.
//

#include "SexyAppFramework/Common.h"

#include "NetworkData.h"
#include "ReflectionBuilder.h"

/////////////// Reflection ///////////////

RT_CLASS_IMPLEMENT(S2C_PVP_PlayerInfos);

void S2C_PVP_PlayerInfos::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(S2C_PVP_DefenderInfo);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(std::wstring, m_name, n);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(int32, m_profileId, pi);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(int32, m_winCup, wc);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(int32, m_lostCup, lc);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(int32, m_winCurrency, wg);
	REFLECTION_CLASSBUILDER_END(S2C_PVP_DefenderInfo);

	REFLECTION_CLASSBUILDER_BEGIN(S2C_PVP_PlayerInfos);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(INetworkData);

		REFLECTION_CLASSBUILDER_FIELD_RENAME(std::string, m_info, di);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(std::string, m_infoMD5, dm);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(S2C_PVP_DefenderInfo, m_defenderInfo, hi);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(std::vector<S2C_PVP_ZombieInfo>, m_zombieInfo, zl);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(int32, m_currency, ag);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(int32, m_cooldown, rt);
	REFLECTION_CLASSBUILDER_END(S2C_PVP_PlayerInfos);

}
