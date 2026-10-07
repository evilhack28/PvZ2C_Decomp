//
//  ZombiePiano.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "ZombiePiano.h"
#include "ZombiePropertySheet.h"

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombiePiano);

void ZombiePiano::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombiePiano);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(Zombie);

	REFLECTION_CLASSBUILDER_END(ZombiePiano);
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombiePianoProps);

void ZombiePianoProps::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombiePianoProps);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ZombiePropertySheet);

		REFLECTION_CLASSBUILDER_FIELD(float, FastMoveSpeed);
	REFLECTION_CLASSBUILDER_END(ZombiePianoProps);
}

bool ZombiePiano::canTargetEntityHeight(BoardEntityHeight i_entityHeight)
{
	return true;
}
