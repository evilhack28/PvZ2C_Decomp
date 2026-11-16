//
//  S2C_ICloud_DoSecretGacha.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-11-12.
//

#include "SexyAppFramework/Common.h"

#include "NetworkData.h"
#include "ReflectionBuilder.h"

/////////////// Reflection ///////////////

RT_CLASS_IMPLEMENT(S2C_ICloud_DoSecretGacha);

void S2C_ICloud_DoSecretGacha::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(S2C_ICloud_DoSecretGacha);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(INetworkData);

		REFLECTION_CLASSBUILDER_FIELD_RENAME(std::vector<S2C_BonusInfo>, bonusList, b);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(S2C_PlayerInfo, playerInfo, p);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(S2C_NewGachaKeyInfo, materialInfo, mi);
	REFLECTION_CLASSBUILDER_END(S2C_ICloud_DoSecretGacha);
}
