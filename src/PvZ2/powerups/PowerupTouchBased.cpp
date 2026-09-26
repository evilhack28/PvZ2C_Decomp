//
//  PowerupTouchBased.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "BasePowerup.h"

PowerupTouchBased::~PowerupTouchBased()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PowerupTouchBased);

void PowerupTouchBased::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PowerupTouchBased);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(BasePowerup);

	REFLECTION_CLASSBUILDER_END(PowerupTouchBased);
}
