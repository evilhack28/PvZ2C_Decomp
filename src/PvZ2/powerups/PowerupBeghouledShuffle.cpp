//
//  PowerupBeghouledShuffle.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "PowerupBeghouled.h"
#include "GameEventMgr.h"

PowerupBeghouledShuffle::PowerupBeghouledShuffle()
{
}

PowerupBeghouledShuffle::~PowerupBeghouledShuffle()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PowerupBeghouledShuffle);

void PowerupBeghouledShuffle::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PowerupBeghouledShuffle);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(BasePowerup);

	REFLECTION_CLASSBUILDER_END(PowerupBeghouledShuffle);
}

void PowerupBeghouledShuffle::onSelected()
{
	gMessageRouter->Broadcast(Message::BeghouledShufflePowerup);
	Activate();
}
