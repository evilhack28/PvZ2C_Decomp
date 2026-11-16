//
//  GridItemGravestoneZombieOnDestruction.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "GridItemGravestoneZombieOnDestruction.h"

GridItemGravestoneZombieOnDestruction::GridItemGravestoneZombieOnDestruction()
{
}

GridItemGravestoneZombieOnDestruction::~GridItemGravestoneZombieOnDestruction()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(GridItemGravestoneZombieOnDestruction);

void GridItemGravestoneZombieOnDestruction::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(GridItemGravestoneZombieOnDestruction);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GridItemGravestone);

	REFLECTION_CLASSBUILDER_END(GridItemGravestoneZombieOnDestruction);
}
