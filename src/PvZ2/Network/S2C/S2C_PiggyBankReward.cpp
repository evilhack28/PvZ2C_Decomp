//
//  S2C_PiggyBankReward.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-11-12.
//

#include "SexyAppFramework/Common.h"

#include "NetworkData.h"
#include "ReflectionBuilder.h"

/////////////// Reflection ///////////////

RT_CLASS_IMPLEMENT(S2C_PiggyBankReward);

void S2C_PiggyBankReward::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(S2C_PiggyBankReward);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(INetworkData);

		REFLECTION_CLASSBUILDER_FIELD_RENAME(int, itemId, i);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(int, amount, q);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(int, gems, g);
	REFLECTION_CLASSBUILDER_END(S2C_PiggyBankReward);

}
