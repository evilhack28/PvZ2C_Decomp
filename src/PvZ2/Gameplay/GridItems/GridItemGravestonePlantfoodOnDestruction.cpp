//
//  GridItemGravestonePlantfoodOnDestruction.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "GridItemGravestonePlantfoodOnDestruction.h"
#include "LawnApp.h"
#include "Board.h"
#include "ReflectionBuilder.h"

/////////////// Lifecycle ///////////////

GridItemGravestonePlantfoodOnDestruction::GridItemGravestonePlantfoodOnDestruction()
{
}

GridItemGravestonePlantfoodOnDestruction::~GridItemGravestonePlantfoodOnDestruction()
{
}

/////////////// Reflection ///////////////

RT_CLASS_IMPLEMENT(GridItemGravestonePlantfoodOnDestruction);

void GridItemGravestonePlantfoodOnDestruction::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(GridItemGravestonePlantfoodOnDestruction);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GridItemGravestone);

	REFLECTION_CLASSBUILDER_END(GridItemGravestonePlantfoodOnDestruction);
}

/////////////// Logic ///////////////

void GridItemGravestonePlantfoodOnDestruction::onKilled()
{
	gLawnApp->m_board->AddPlantfood(GetPosition());
}
