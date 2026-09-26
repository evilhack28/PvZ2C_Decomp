//
//  PowerupTypeBeghouledShuffle.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "PowerupBeghouled.h"

PowerupTypeBeghouledShuffle::PowerupTypeBeghouledShuffle()
{
}

PowerupTypeBeghouledShuffle::~PowerupTypeBeghouledShuffle()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PowerupTypeBeghouledShuffle);

void PowerupTypeBeghouledShuffle::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PowerupTypeBeghouledShuffle);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PowerupType);

	REFLECTION_CLASSBUILDER_END(PowerupTypeBeghouledShuffle);
}
