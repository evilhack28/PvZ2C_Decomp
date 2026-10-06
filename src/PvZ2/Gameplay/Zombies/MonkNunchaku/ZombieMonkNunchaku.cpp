//
//  ZombieMonkNunchaku.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "ZombieMonkNunchaku.h"
#include "ZombiePropertySheet.h"

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieMonkNunchaku);

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieMonkNunchakuProps);

void ZombieMonkNunchakuProps::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombieMonkNunchakuProps);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ZombieHammerProps);

	REFLECTION_CLASSBUILDER_END(ZombieMonkNunchakuProps);
}
