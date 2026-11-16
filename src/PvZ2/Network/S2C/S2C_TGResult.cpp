//
//  S2C_TGResult.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-11-12.
//

#include "SexyAppFramework/Common.h"

#include "NetworkData.h"
#include "ReflectionBuilder.h"

/////////////// Reflection ///////////////

RT_CLASS_IMPLEMENT(S2C_TGResult);

void S2C_TGResult::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(S2C_TGResult);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(INetworkData);

		REFLECTION_CLASSBUILDER_FIELD_RENAME(int, GoldCost, g);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(std::vector<S2C_BonusInfo>, CostList, l);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(std::vector<S2C_BonusInfo>, ProductList, gl);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(S2C_PlayerInfo, PlayerInfo, p);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(int, m_adTimes, times);
	REFLECTION_CLASSBUILDER_END(S2C_TGResult);

}
