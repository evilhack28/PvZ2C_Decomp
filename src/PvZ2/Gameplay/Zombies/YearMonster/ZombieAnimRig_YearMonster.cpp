//
//  ZombieAnimRig_YearMonster.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "ZombieYearMonster.h"

ZombieAnimRig_YearMonster::ZombieAnimRig_YearMonster()
{
}

ZombieAnimRig_YearMonster::~ZombieAnimRig_YearMonster()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieAnimRig_YearMonster);

void ZombieAnimRig_YearMonster::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombieAnimRig_YearMonster);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ZombieAnimRig);

	REFLECTION_CLASSBUILDER_END(ZombieAnimRig_YearMonster);
}
