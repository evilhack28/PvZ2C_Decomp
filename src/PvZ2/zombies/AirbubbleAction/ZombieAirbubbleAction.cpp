//
//  ZombieAirbubbleAction.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "ZombieAirbubbleAction.h"

ZombieAirbubbleAction::ZombieAirbubbleAction()
{
}

ZombieAirbubbleAction::~ZombieAirbubbleAction()
{
}

ZombieAirbubbleActionProps::~ZombieAirbubbleActionProps()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieAirbubbleAction);

void ZombieAirbubbleAction::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombieAirbubbleAction);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(WaveAction);

	REFLECTION_CLASSBUILDER_END(ZombieAirbubbleAction);
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieAirbubbleActionProps);

void ZombieAirbubbleActionProps::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombieAirbubbleActionProps);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(WaveActionProperties);

		REFLECTION_CLASSBUILDER_FIELD(int, BubbleNumber);
	REFLECTION_CLASSBUILDER_END(ZombieAirbubbleActionProps);
}

void ZombieAirbubbleAction::WaveUpdate(int i_arg0, Sexy::MTRand & i_arg1)
{
}

void ZombieAirbubbleAction::WaveEnd(int i_arg0, Sexy::MTRand & i_arg1)
{
}
