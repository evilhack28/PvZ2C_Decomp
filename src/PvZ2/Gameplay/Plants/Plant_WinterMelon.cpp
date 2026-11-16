//
//  Plant_WinterMelon.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "Plant_WinterMelon.h"

PlantWinterMelon::~PlantWinterMelon()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantWinterMelon);

void PlantWinterMelon::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantWinterMelon);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantMelonpult);

		REFLECTION_CLASSBUILDER_FIELD(bool, m_level5);
		REFLECTION_CLASSBUILDER_FIELD(float, BoostFreezeValue);
	REFLECTION_CLASSBUILDER_END(PlantWinterMelon);
}
