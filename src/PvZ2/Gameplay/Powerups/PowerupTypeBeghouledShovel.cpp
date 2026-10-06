//
//  PowerupTypeBeghouledShovel.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "PowerupBeghouled.h"

PowerupTypeBeghouledShovel::PowerupTypeBeghouledShovel()
{
}

PowerupTypeBeghouledShovel::~PowerupTypeBeghouledShovel()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PowerupTypeBeghouledShovel);

void PowerupTypeBeghouledShovel::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PowerupTypeBeghouledShovel);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PowerupType);

	REFLECTION_CLASSBUILDER_END(PowerupTypeBeghouledShovel);
}
