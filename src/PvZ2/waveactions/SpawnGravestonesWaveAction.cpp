//
//  SpawnGravestonesWaveAction.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "SpawnGravestonesWaveAction.h"

SpawnGravestonesWaveAction::SpawnGravestonesWaveAction()
{
}

SpawnGravestonesWaveAction::~SpawnGravestonesWaveAction()
{
}

SpawnGravestonesWaveActionProps::SpawnGravestonesWaveActionProps()
{
}

SpawnGravestonesWaveActionProps::~SpawnGravestonesWaveActionProps()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(SpawnGravestonesWaveAction);

void SpawnGravestonesWaveAction::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(SpawnGravestonesWaveAction);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(SpawnGridItemsWaveAction);

	REFLECTION_CLASSBUILDER_END(SpawnGravestonesWaveAction);
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(SpawnGravestonesWaveActionProps);

void SpawnGravestonesWaveActionProps::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(SpawnGravestonesWaveActionProps);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(SpawnGridItemsWaveActionProps);

	REFLECTION_CLASSBUILDER_FIELD(std::vector<GridItemPoolEntry>, GravestonePool);
	REFLECTION_CLASSBUILDER_FIELD(std::vector<Point>, SpawnPositionsPool);
	REFLECTION_CLASSBUILDER_FIELD(Rect, SpawnPositionsRect);

	REFLECTION_CLASSBUILDER_END(SpawnGravestonesWaveActionProps);
}
