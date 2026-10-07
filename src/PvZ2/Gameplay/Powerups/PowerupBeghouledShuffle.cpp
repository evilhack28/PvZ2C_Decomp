//
//  PowerupBeghouledShuffle.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "PowerupBeghouled.h"
#include "GameEventMgr.h"
#include "ReflectionBuilder.h"

/////////////// Lifecycle ///////////////

PowerupBeghouledShuffle::PowerupBeghouledShuffle()
{
}

PowerupBeghouledShuffle::~PowerupBeghouledShuffle()
{
}

/////////////// Reflection ///////////////

RT_CLASS_IMPLEMENT(PowerupBeghouledShuffle);

void PowerupBeghouledShuffle::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PowerupBeghouledShuffle);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(BasePowerup);

	REFLECTION_CLASSBUILDER_END(PowerupBeghouledShuffle);
}

/////////////// Logic ///////////////

void PowerupBeghouledShuffle::onSelected()
{
	gMessageRouter->Broadcast(Message::BeghouledShufflePowerup);
	Activate();
}
