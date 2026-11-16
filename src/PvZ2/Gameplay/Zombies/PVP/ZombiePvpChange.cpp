//
//  ZombiePvpChange.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "ZombiePvpChange.h"

ZombiePvpChange::ZombiePvpChange()
{
}

ZombiePvpChange::~ZombiePvpChange()
{
}

ZombiePvpChangeProps::~ZombiePvpChangeProps()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombiePvpChange);

void ZombiePvpChange::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombiePvpChange);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ZombieBasic);

		REFLECTION_CLASSBUILDER_FIELD(float, m_skillTime);
	REFLECTION_CLASSBUILDER_END(ZombiePvpChange);
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombiePvpChangeProps);

void ZombiePvpChangeProps::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombiePvpChangeProps);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ZombiePropertySheet);

	REFLECTION_CLASSBUILDER_END(ZombiePvpChangeProps);
}
