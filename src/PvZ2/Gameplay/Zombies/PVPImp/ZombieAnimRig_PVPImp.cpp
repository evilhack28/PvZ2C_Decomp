//
//  ZombieAnimRig_PVPImp.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "ZombiePVPImp.h"
#include "ReflectionBuilder.h"

/////////////// Lifecycle ///////////////

ZombieAnimRig_PVPImp::~ZombieAnimRig_PVPImp()
{
}

/////////////// Reflection ///////////////

RT_CLASS_IMPLEMENT(ZombieAnimRig_PVPImp);

void ZombieAnimRig_PVPImp::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombieAnimRig_PVPImp);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ZombieAnimRig_Imp);

	REFLECTION_CLASSBUILDER_END(ZombieAnimRig_PVPImp);
}
