//
//  ZombieSurrenderSubsystem.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "ZombieSurrenderSubsystem.h"

ZombieSurrenderSubsystem::ZombieSurrenderSubsystem()
{
}

ZombieSurrenderSubsystem::~ZombieSurrenderSubsystem()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieSurrenderSubsystem);

void ZombieSurrenderSubsystem::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombieSurrenderSubsystem);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GameSubSystem);

	REFLECTION_CLASSBUILDER_END(ZombieSurrenderSubsystem);
}
