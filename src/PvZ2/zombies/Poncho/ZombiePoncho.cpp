//
//  ZombiePoncho.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "ZombiePoncho.h"
#include "ZombiePropertySheet.h"

ZombiePonchoProps::~ZombiePonchoProps()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombiePoncho);

void ZombiePoncho::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombiePoncho);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(Zombie);

		REFLECTION_CLASSBUILDER_FIELD(int32, m_helmDamageIndex);
		REFLECTION_CLASSBUILDER_FIELD(bool, m_hasPlate);
	REFLECTION_CLASSBUILDER_END(ZombiePoncho);
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombiePonchoProps);

void ZombiePonchoProps::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombiePonchoProps);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ZombiePropertySheet);

	REFLECTION_CLASSBUILDER_END(ZombiePonchoProps);
}
