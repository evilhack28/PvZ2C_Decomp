//
//  ZombieEightiesMC.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "ZombieEightiesMC.h"

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieEightiesMC);

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieEightiesMCProps);

void ZombieEightiesMCProps::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombieEightiesMCProps);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ZombiePropertySheet);

		REFLECTION_CLASSBUILDER_FIELD(std::string, JamStyle);
	REFLECTION_CLASSBUILDER_END(ZombieEightiesMCProps);
}
