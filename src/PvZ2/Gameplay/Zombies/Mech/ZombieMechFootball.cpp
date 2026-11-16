//
//  ZombieMechFootball.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "ZombieMechFootball.h"
#include "ZombiePropertySheet.h"

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieMechFootball);

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieMechFootballProps);

void ZombieMechFootballProps::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombieMechFootballProps);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ZombieMechProps);

		REFLECTION_CLASSBUILDER_FIELD(RtWeakPtr<ProjectilePropertySheet>, Football);
	REFLECTION_CLASSBUILDER_END(ZombieMechFootballProps);
}
