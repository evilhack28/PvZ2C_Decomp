//
//  PowerupBeghouledShovel.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "PowerupBeghouled.h"

PowerupBeghouledShovel::PowerupBeghouledShovel()
{
}

PowerupBeghouledShovel::~PowerupBeghouledShovel()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PowerupBeghouledShovel);

void PowerupBeghouledShovel::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PowerupBeghouledShovel);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PowerupTouchBased);

	REFLECTION_CLASSBUILDER_END(PowerupBeghouledShovel);
}

bool PowerupBeghouledShovel::onTouchBegin(const Sexy::Touch& i_arg)
{
	return true;
}
