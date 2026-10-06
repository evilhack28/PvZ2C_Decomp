//
//  GridItemRollerAnimRig.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "GridItemRenaiRoller.h"

GridItemRollerAnimRig::GridItemRollerAnimRig()
{
}

GridItemRollerAnimRig::~GridItemRollerAnimRig()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(GridItemRollerAnimRig);

void GridItemRollerAnimRig::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(GridItemRollerAnimRig);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PopAnimRig);

	REFLECTION_CLASSBUILDER_END(GridItemRollerAnimRig);
}

void GridItemRollerAnimRig::PlayRoll(PopAnimRig::AnimStoppedReflectionDelegate i_arg)
{
}
