//
//  ZombieInvisiblePlane.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "ZombieInvisiblePlane.h"

ZombieInvisiblePlaneProps::ZombieInvisiblePlaneProps()
{
	DamageLayerIndices = 1;
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieInvisiblePlane);

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieInvisiblePlaneProps);

void ZombieInvisiblePlaneProps::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombieInvisiblePlaneProps);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ZombieSkyCityProps);

		REFLECTION_CLASSBUILDER_FIELD(int, DamageLayerIndices);
	REFLECTION_CLASSBUILDER_END(ZombieInvisiblePlaneProps);
}

bool ZombieInvisiblePlane::canTargetEntityHeight(BoardEntityHeight i_arg)
{
	return true;
}
