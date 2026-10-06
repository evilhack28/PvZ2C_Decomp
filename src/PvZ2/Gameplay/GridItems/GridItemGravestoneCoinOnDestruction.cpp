//
//  GridItemGravestoneCoinOnDestruction.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "GridItemGravestoneSunOnDestruction.h"

GridItemGravestoneCoinOnDestruction::GridItemGravestoneCoinOnDestruction()
{
}

GridItemGravestoneCoinOnDestruction::~GridItemGravestoneCoinOnDestruction()
{
}

GridItemGravestoneCoinOnDestructionPropertySheet::~GridItemGravestoneCoinOnDestructionPropertySheet()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(GridItemGravestoneCoinOnDestruction);

void GridItemGravestoneCoinOnDestruction::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(GridItemGravestoneCoinOnDestruction);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GridItemGravestone);

	REFLECTION_CLASSBUILDER_END(GridItemGravestoneCoinOnDestruction);
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(GridItemGravestoneCoinOnDestructionPropertySheet);

void GridItemGravestoneCoinOnDestructionPropertySheet::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(GridItemGravestoneCoinOnDestructionPropertySheet);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GridItemGravestonePropertySheet);

		REFLECTION_CLASSBUILDER_FIELD(int32, AmountToSpawn);
	REFLECTION_CLASSBUILDER_END(GridItemGravestoneCoinOnDestructionPropertySheet);
}
