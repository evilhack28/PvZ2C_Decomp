//
//  VictoryOutro.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-04.
//

#include "SexyAppFramework/Common.h"

#include "VictoryOutro.h"

/////////////// VictoryOutroProperties ///////////////

RT_CLASS_IMPLEMENT(VictoryOutroProperties);

void VictoryOutroProperties::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(VictoryOutroProperties);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(OutroModuleProperties);

		REFLECTION_CLASSBUILDER_FIELD(float, FlagSpawnTime);
		REFLECTION_CLASSBUILDER_FIELD(int32, BaseCoinAwardValue);
		REFLECTION_CLASSBUILDER_FIELD(int32, CoinsPerMower);
		REFLECTION_CLASSBUILDER_FIELD(float, CoinShowerStartTime);
		REFLECTION_CLASSBUILDER_FIELD(float, CoinShowerDuration);
		REFLECTION_CLASSBUILDER_FIELD(float, CoinShowerDelayBetweenMowers);
		REFLECTION_CLASSBUILDER_FIELD(float, CoinInitialHeight);
		REFLECTION_CLASSBUILDER_FIELD(float, CoinCollectTime);
		REFLECTION_CLASSBUILDER_FIELD(float, AdditionalEndingDelay);
	REFLECTION_CLASSBUILDER_END(VictoryOutroProperties);
}
