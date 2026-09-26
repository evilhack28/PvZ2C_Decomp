//
//  ZombieRomanImp.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "ZombieRomanImp.h"

ZombieRomanImpProps::~ZombieRomanImpProps()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieRomanImpProps);

void ZombieRomanImpProps::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombieRomanImpProps);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ZombiePropertySheet);

	REFLECTION_CLASSBUILDER_FIELD(int, NetSuspendSeconds);

	REFLECTION_CLASSBUILDER_END(ZombieRomanImpProps);
}

void ZombieRomanImp::onPreImpFlight()
{
}
