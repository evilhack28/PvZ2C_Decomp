//
//  GridItemAction.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "GridItemEntityTargeting.h"

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(GridItemAction);

void GridItemAction::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(GridItemAction);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PropertySheetBase);

	REFLECTION_CLASSBUILDER_FIELD(std::vector<ZombieConditionEntry>, ZConditions);
	REFLECTION_CLASSBUILDER_FIELD(std::vector<PlantConditionEntry>, PConditions);
	REFLECTION_CLASSBUILDER_FIELD(std::vector<GridItemConditionEntry>, GConditions);
	REFLECTION_CLASSBUILDER_FIELD(GridItemEffectType, Type);
	REFLECTION_CLASSBUILDER_FIELD(std::vector<TeamFlags>, TeamsToAffect);
	REFLECTION_CLASSBUILDER_FIELD(std::vector<BoardEntityTypeFlag>, EntitiesToAffect);
	REFLECTION_CLASSBUILDER_FIELD(GridItemTargetingArea, TargetArea);
	REFLECTION_CLASSBUILDER_FIELD(pvztime_t, HitAnimLoopTime);
	REFLECTION_CLASSBUILDER_FIELD(Point, HitAffectOffset);

	REFLECTION_CLASSBUILDER_END(GridItemAction);
}
