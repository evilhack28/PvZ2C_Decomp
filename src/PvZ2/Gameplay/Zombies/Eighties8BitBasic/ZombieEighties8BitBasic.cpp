//
//  ZombieEighties8BitBasic.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "ZombieEighties8BitBasic.h"

ZombieEighties8BitBasic::ZombieEighties8BitBasic()
{
}

ZombieEighties8BitBasic::~ZombieEighties8BitBasic()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieEighties8BitBasic);

void ZombieEighties8BitBasic::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombieEighties8BitBasic);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ZombieEightiesBasic);

	REFLECTION_CLASSBUILDER_END(ZombieEighties8BitBasic);
}
