//
//  ZombiePvpDead.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "ZombiePvpDead.h"

ZombiePvpDeadProps::~ZombiePvpDeadProps()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombiePvpDead);

void ZombiePvpDead::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombiePvpDead);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ZombieTombRaiser);

		REFLECTION_CLASSBUILDER_FIELD(float, m_skillTime);
	REFLECTION_CLASSBUILDER_END(ZombiePvpDead);
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombiePvpDeadProps);

void ZombiePvpDeadProps::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombiePvpDeadProps);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ZombieTombRaiserProps);

	REFLECTION_CLASSBUILDER_END(ZombiePvpDeadProps);
}

#include "ZombieTombRaiser.h"
void ZombiePvpDead::onThrow()
{
	 ZombieTombRaiser::onThrow();
}
