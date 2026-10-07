//
//  ZombossIceBall.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "ZombiePropertySheet.h"
#include "ZombossIceBall.h"

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombossIceBall);

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombossIceBallProps);

void ZombossIceBallProps::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombossIceBallProps);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ZombiePropertySheet);

		REFLECTION_CLASSBUILDER_FIELD(float, ReduceHitPointPercent);
	REFLECTION_CLASSBUILDER_END(ZombossIceBallProps);
}

bool ZombossIceBall::canTargetEntityHeight(BoardEntityHeight i_entityHeight)
{
	return true;
}
