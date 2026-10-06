//
//  GridItemPropertySheet.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "GridItemPropertySheet.h"

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(GridItemPropertySheet);

void GridItemPropertySheet::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(GridItemLevelStat);
		REFLECTION_CLASSBUILDER_FIELD(float, HitPointsLevel);
	REFLECTION_CLASSBUILDER_END(GridItemLevelStat);

	REFLECTION_CLASSBUILDER_BEGIN(GridItemPropertySheet);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PropertySheetBase);

		REFLECTION_CLASSBUILDER_FIELD(std::vector<std::string>, PlantsCanAttackList);
		REFLECTION_CLASSBUILDER_FIELD(std::vector<GridItemLevelStat>, GridItemLevelStats);
		REFLECTION_CLASSBUILDER_FIELD(BoardEntityHeight, Height);
		REFLECTION_CLASSBUILDER_FIELD(bool, CanBeMowed);
		REFLECTION_CLASSBUILDER_FIELD(PlantingRestrictionSet, PlantingRestrictions);
	REFLECTION_CLASSBUILDER_END(GridItemPropertySheet);
}
