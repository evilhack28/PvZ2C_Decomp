//
//  ZombieLionDance.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "ZombieLionDance.h"

ZombieLionDanceProps::~ZombieLionDanceProps()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieLionDance);

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieLionDanceProps);

void ZombieLionDanceProps::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombieLionDanceProps);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ZombiePropertySheet);

		REFLECTION_CLASSBUILDER_FIELD(pvztime_t, MoveTime);
		REFLECTION_CLASSBUILDER_FIELD(int, MaxColumnReach);
	REFLECTION_CLASSBUILDER_END(ZombieLionDanceProps);
}

bool ZombieLionDance::canTargetEntityHeight(BoardEntityHeight i_entityHeight)
{
	return true;
}
