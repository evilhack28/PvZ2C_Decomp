//
//  GridItemGravestoneSunOnDestruction.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "GridItemGravestoneSunOnDestruction.h"

GridItemGravestoneSunOnDestruction::GridItemGravestoneSunOnDestruction()
{
}

GridItemGravestoneSunOnDestruction::~GridItemGravestoneSunOnDestruction()
{
}

GridItemGravestoneSunOnDestructionPropertySheet::~GridItemGravestoneSunOnDestructionPropertySheet()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(GridItemGravestoneSunOnDestruction);

void GridItemGravestoneSunOnDestruction::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(GridItemGravestoneSunOnDestruction);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GridItemGravestone);

	REFLECTION_CLASSBUILDER_END(GridItemGravestoneSunOnDestruction);
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(GridItemGravestoneSunOnDestructionPropertySheet);

void GridItemGravestoneSunOnDestructionPropertySheet::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(GridItemGravestoneSunOnDestructionPropertySheet);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GridItemGravestonePropertySheet);

		REFLECTION_CLASSBUILDER_FIELD(int32, AmountToSpawn);
	REFLECTION_CLASSBUILDER_END(GridItemGravestoneSunOnDestructionPropertySheet);
}
