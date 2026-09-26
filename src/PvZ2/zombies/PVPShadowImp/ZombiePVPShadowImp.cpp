//
//  ZombiePVPShadowImp.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "ZombiePVPImp.h"

ZombiePVPShadowImpProps::~ZombiePVPShadowImpProps()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombiePVPShadowImpProps);

void ZombiePVPShadowImpProps::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombiePVPShadowImpProps);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ZombiePropertySheet);

	REFLECTION_CLASSBUILDER_FIELD(pvztime_t, ShadowTime);

	REFLECTION_CLASSBUILDER_END(ZombiePVPShadowImpProps);
}

void ZombiePVPShadowImp::ApplyZombieFood()
{
}
