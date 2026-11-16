//
//  ZombieAnimRig_ModernAllStar.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "ZombieModernAllStar.h"

ZombieAnimRig_ModernAllStar::ZombieAnimRig_ModernAllStar()
{
}

ZombieAnimRig_ModernAllStar::~ZombieAnimRig_ModernAllStar()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieAnimRig_ModernAllStar);

void ZombieAnimRig_ModernAllStar::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombieAnimRig_ModernAllStar);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ZombieAnimRig);

	REFLECTION_CLASSBUILDER_END(ZombieAnimRig_ModernAllStar);
}
