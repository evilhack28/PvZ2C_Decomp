//
//  Plant_Dusklobber.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "Plant_Dusklobber.h"

PlantDusklobber::PlantDusklobber()
{
}

PlantDusklobber::~PlantDusklobber()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantDusklobber);

void PlantDusklobber::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantDusklobber);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantFramework);

		REFLECTION_CLASSBUILDER_FIELD(int32_t, m_timesSpecialFired);
	REFLECTION_CLASSBUILDER_END(PlantDusklobber);
}

#include "Plant_Dusklobber.h"
void PlantDusklobber::UpdateActions()
{
	 PlantDusklobber::updateRigLayers();
}

#include "PlantFramework.h"
void PlantDusklobber::CancelPlantfood()
{
	 PlantFramework::CancelPlantfood();
}

bool PlantDusklobber::CanApplyPlantfood()
{
	return true;
}
