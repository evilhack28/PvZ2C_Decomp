//
//  ZombieTosser_SubSystem.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "ZombieTosser_SubSystem.h"

ZombieTosserSubSystem::ZombieTosserSubSystem()
{
}

ZombieTosserSubSystem::~ZombieTosserSubSystem()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieTosserSubSystem);

void ZombieTosserSubSystem::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(TossedZombie);
	REFLECTION_CLASSBUILDER_END(TossedZombie);

	REFLECTION_CLASSBUILDER_BEGIN(ZombieTosserSubSystem);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GameSubSystem);

	REFLECTION_CLASSBUILDER_END(ZombieTosserSubSystem);
}
