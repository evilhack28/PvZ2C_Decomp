//
//  ZombieMirrorQueen.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "ZombieMirrorQueen.h"

ZombieMirrorQueenProps::~ZombieMirrorQueenProps()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieMirrorQueen);

void ZombieMirrorQueen::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombieMirrorQueen);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ZombieWithActions);

	REFLECTION_CLASSBUILDER_END(ZombieMirrorQueen);
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieMirrorQueenProps);

void ZombieMirrorQueenProps::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombieMirrorQueenProps);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ZombieWithActionsProps);

		REFLECTION_CLASSBUILDER_FIELD(int, Phase);
	REFLECTION_CLASSBUILDER_END(ZombieMirrorQueenProps);
}

void ZombieMirrorQueen::SetIdleState()
{
}

void ZombieMirrorQueen::SetGrabbedState()
{
}

void ZombieMirrorQueen::SetWalkingState()
{
}

bool ZombieMirrorQueen::isImmuneToShrinking()
{
	return true;
}
