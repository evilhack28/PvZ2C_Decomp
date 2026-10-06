//
//  GridItemSpeakerZomboss.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "GridItemSpeaker.h"

GridItemSpeakerZomboss::GridItemSpeakerZomboss()
{
	m_wantsToClearLane = 0;
}

GridItemSpeakerZomboss::~GridItemSpeakerZomboss()
{
}

GridItemSpeakerZombossProps::GridItemSpeakerZombossProps()
{
}

GridItemSpeakerZombossProps::~GridItemSpeakerZombossProps()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(GridItemSpeakerZomboss);

void GridItemSpeakerZomboss::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(GridItemSpeakerZomboss);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GridItemSpeaker);

		REFLECTION_CLASSBUILDER_FIELD(bool, m_wantsToClearLane);
	REFLECTION_CLASSBUILDER_END(GridItemSpeakerZomboss);
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(GridItemSpeakerZombossProps);

void GridItemSpeakerZombossProps::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(GridItemSpeakerZombossProps);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GridItemSpeakerProps);

		REFLECTION_CLASSBUILDER_FIELD(SexyVector2, ShockWaveSpawnOffset);
	REFLECTION_CLASSBUILDER_END(GridItemSpeakerZombossProps);
}
