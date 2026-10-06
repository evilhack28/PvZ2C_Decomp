//
//  SpawnPumpkinScarecrowWaveAction.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "SpawnPumpkinScarecrowWaveAction.h"

SpawnPumpkinScarecrowWaveAction::SpawnPumpkinScarecrowWaveAction()
{
}

SpawnPumpkinScarecrowWaveAction::~SpawnPumpkinScarecrowWaveAction()
{
}

SpawnPumpkinScarecrowWaveActionProps::SpawnPumpkinScarecrowWaveActionProps()
{
	Level = 1;
}

SpawnPumpkinScarecrowWaveActionProps::~SpawnPumpkinScarecrowWaveActionProps()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(SpawnPumpkinScarecrowWaveAction);

void SpawnPumpkinScarecrowWaveAction::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(SpawnPumpkinScarecrowWaveAction);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(SpawnGridItemsWaveAction);

	REFLECTION_CLASSBUILDER_END(SpawnPumpkinScarecrowWaveAction);
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(SpawnPumpkinScarecrowWaveActionProps);

void SpawnPumpkinScarecrowWaveActionProps::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(SpawnPumpkinScarecrowWaveActionProps);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(SpawnGridItemsWaveActionProps);

		REFLECTION_CLASSBUILDER_FIELD(std::vector<GridItemPoolEntry>, PumpkinScarecrowPool);
		REFLECTION_CLASSBUILDER_FIELD(std::vector<Point>, SpawnPositionsPool);
		REFLECTION_CLASSBUILDER_FIELD(Rect, SpawnPositionsRect);
		REFLECTION_CLASSBUILDER_FIELD(float, Hitpoints);
		REFLECTION_CLASSBUILDER_FIELD(int, Level);
	REFLECTION_CLASSBUILDER_END(SpawnPumpkinScarecrowWaveActionProps);
}
