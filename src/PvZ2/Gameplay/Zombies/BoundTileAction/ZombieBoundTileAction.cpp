//
//  ZombieBoundTileAction.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "ZombiePotionAction.h"

ZombieBoundTileAction::ZombieBoundTileAction()
{
}

ZombieBoundTileAction::~ZombieBoundTileAction()
{
}

ZombieBoundTileActionProps::~ZombieBoundTileActionProps()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieBoundTileAction);

void ZombieBoundTileAction::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombieBoundTileAction);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(WaveAction);

	REFLECTION_CLASSBUILDER_END(ZombieBoundTileAction);
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieBoundTileActionProps);

void ZombieBoundTileActionProps::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombieBoundTileActionProps);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(WaveActionProperties);

		REFLECTION_CLASSBUILDER_FIELD(std::vector<PotionData>, Tiles);
	REFLECTION_CLASSBUILDER_END(ZombieBoundTileActionProps);
}

void ZombieBoundTileAction::WaveUpdate(int i_arg0, Sexy::MTRand & i_arg1)
{
}

void ZombieBoundTileAction::WaveEnd(int i_arg0, Sexy::MTRand & i_arg1)
{
}
