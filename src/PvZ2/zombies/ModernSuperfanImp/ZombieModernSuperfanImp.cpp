//
//  ZombieModernSuperfanImp.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "ZombieModernSuperfanImp.h"

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieModernSuperfanImp);

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieModernSuperfanImpProps);

void ZombieModernSuperfanImpProps::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombieModernSuperfanImpProps);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ZombiePropertySheet);

	REFLECTION_CLASSBUILDER_END(ZombieModernSuperfanImpProps);
}
