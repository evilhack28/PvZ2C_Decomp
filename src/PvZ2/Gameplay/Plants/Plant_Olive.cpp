//
//  Plant_Olive.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "Plant_Olive.h"

PlantOlive::~PlantOlive()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantOlive);

void PlantOlive::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantOlive);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantFramework);

	REFLECTION_CLASSBUILDER_FIELD(pvztime_t, m_idleEnd);
	REFLECTION_CLASSBUILDER_FIELD(RtWeakPtr<OliveOilSystem>, m_systemPtr);

	REFLECTION_CLASSBUILDER_END(PlantOlive);
}
