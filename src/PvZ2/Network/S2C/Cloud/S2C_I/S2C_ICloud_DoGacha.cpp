//
//  S2C_ICloud_DoGacha.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-11-12.
//

#include "SexyAppFramework/Common.h"

#include "NetworkData.h"
#include "ReflectionBuilder.h"

/////////////// Reflection ///////////////

RT_CLASS_IMPLEMENT(S2C_ICloud_DoGacha);

void S2C_ICloud_DoGacha::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(S2C_ICloud_DoGacha);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(INetworkData);

		REFLECTION_CLASSBUILDER_FIELD_RENAME(S2C_GachaInfo, gachaInfo, g);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(std::vector<S2C_BonusInfo>, bonusList, bl);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(S2C_PlayerInfo, playerInfo, p);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(int, returnGems, rg);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(int, times, t);
	REFLECTION_CLASSBUILDER_END(S2C_ICloud_DoGacha);
}
