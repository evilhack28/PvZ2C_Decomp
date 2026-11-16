//
//  Plant_Sunpod.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "Plant_SunPod.h"

PlantSunpod::PlantSunpod()
{
	m_level = 0;
}

PlantSunpod::~PlantSunpod()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantSunpod);

void PlantSunpod::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantSunpod);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantFramework);

		REFLECTION_CLASSBUILDER_FIELD(int32, m_level);
	REFLECTION_CLASSBUILDER_END(PlantSunpod);
}

bool PlantSunpod::CanApplyPlantfood()
{
	return true;
}
