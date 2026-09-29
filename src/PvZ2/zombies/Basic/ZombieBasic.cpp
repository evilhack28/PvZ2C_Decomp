//
//  ZombieBasic.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "ZombieBasic.h"

ZombieBasic::ZombieBasic()
{
}

ZombieBasic::~ZombieBasic()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieBasic);

void ZombieBasic::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombieBasic);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(Zombie);

		REFLECTION_CLASSBUILDER_FIELD(float, m_lastFrame);
		REFLECTION_CLASSBUILDER_FIELD(int32, m_helmDamageIndex);
	REFLECTION_CLASSBUILDER_END(ZombieBasic);
}
