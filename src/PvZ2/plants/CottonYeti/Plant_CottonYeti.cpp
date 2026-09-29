//
//  Plant_CottonYeti.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "Plant_CottonYeti.h"

PlantCottonYeti::PlantCottonYeti()
{
}

PlantCottonYeti::~PlantCottonYeti()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantCottonYeti);

void PlantCottonYeti::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantCottonYeti);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantFramework);

		REFLECTION_CLASSBUILDER_FIELD(pvztime_t, m_prepareTime);
	REFLECTION_CLASSBUILDER_END(PlantCottonYeti);
}

#include "PlantFramework.h"
void PlantCottonYeti::ApplyPlantfood()
{
	 PlantFramework::ApplyPlantfood();
}

#include "PlantFramework.h"
void PlantCottonYeti::CancelPlantfood()
{
	 PlantFramework::CancelPlantfood();
}

void PlantCottonYeti::UpdatePlantfood()
{
}

bool PlantCottonYeti::CanApplyPlantfood()
{
	return true;
}
