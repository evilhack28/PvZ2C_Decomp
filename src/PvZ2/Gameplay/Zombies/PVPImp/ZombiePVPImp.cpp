//
//  ZombiePVPImp.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "ZombiePVPImp.h"

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombiePVPImp);

void ZombiePVPImp::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombiePVPImp);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ZombieImp);

	REFLECTION_CLASSBUILDER_END(ZombiePVPImp);
}
