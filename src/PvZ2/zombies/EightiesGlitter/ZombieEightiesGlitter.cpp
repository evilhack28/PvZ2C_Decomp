//
//  ZombieEightiesGlitter.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "ZombieEightiesGlitter.h"

ZombieEightiesGlitterProps::~ZombieEightiesGlitterProps()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieEightiesGlitter);

void ZombieEightiesGlitter::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombieEightiesGlitter);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(Zombie);

		REFLECTION_CLASSBUILDER_FIELD(pvztime_t, m_lastApplicationTime);
	REFLECTION_CLASSBUILDER_END(ZombieEightiesGlitter);
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieEightiesGlitterProps);

void ZombieEightiesGlitterProps::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombieEightiesGlitterProps);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ZombiePropertySheet);

		REFLECTION_CLASSBUILDER_FIELD(std::string, JamStyle);
		REFLECTION_CLASSBUILDER_FIELD(int, RainbowTrailLength);
	REFLECTION_CLASSBUILDER_END(ZombieEightiesGlitterProps);
}
