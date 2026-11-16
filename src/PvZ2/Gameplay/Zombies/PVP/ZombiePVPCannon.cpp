//
//  ZombiePVPCannon.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "ZombiePVPCannon.h"
#include "ZombiePropertySheet.h"

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombiePVPCannon);

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombiePVPCannonProps);

void ZombiePVPCannonProps::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombiePVPCannonProps);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ZombiePropertySheet);

	REFLECTION_CLASSBUILDER_END(ZombiePVPCannonProps);
}
