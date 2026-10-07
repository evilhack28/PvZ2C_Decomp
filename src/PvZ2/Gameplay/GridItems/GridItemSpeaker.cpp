//
//  GridItemSpeaker.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "GridItemSpeaker.h"

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(GridItemSpeaker);

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(GridItemSpeakerProps);

void GridItemSpeakerProps::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(GridItemSpeakerProps);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GridItemBreakableTargetProps);

		REFLECTION_CLASSBUILDER_FIELD(int, SonicDamageAmount);
	REFLECTION_CLASSBUILDER_END(GridItemSpeakerProps);
}

PlantingReason GridItemSpeaker::GetCantPlantReason() const
{
	return PLANTING_NOT_ON_SPEAKER;
}
