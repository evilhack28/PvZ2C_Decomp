//
//  Plant_Turnip.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "Plant_Turnip.h"

PlantTurnip::~PlantTurnip()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantTurnip);

void PlantTurnip::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantTurnip);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantFramework);

		REFLECTION_CLASSBUILDER_FIELD(bool, m_searchingLeft);
		REFLECTION_CLASSBUILDER_FIELD(pvztime_t, m_defendDuration);
	REFLECTION_CLASSBUILDER_END(PlantTurnip);
}
