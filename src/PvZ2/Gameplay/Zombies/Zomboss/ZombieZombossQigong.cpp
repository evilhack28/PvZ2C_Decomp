//
//  ZombieZombossQigong.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "ZombieZombossQigong.h"

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieZombossQigong);

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieZombossQigongProps);

void ZombieZombossQigongProps::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombossQigongStage);
		REFLECTION_CLASSBUILDER_FIELD(Sexy::Rect, moveRect);
		REFLECTION_CLASSBUILDER_FIELD(CZombieSummonDataPool, ZombieSummonDataPool);
	REFLECTION_CLASSBUILDER_END(ZombossQigongStage);

	REFLECTION_CLASSBUILDER_BEGIN(ZombieZombossQigongProps);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ZombossProps);

		REFLECTION_CLASSBUILDER_FIELD(std::vector<ZombossQigongStage>, Stages);
	REFLECTION_CLASSBUILDER_END(ZombieZombossQigongProps);
}
