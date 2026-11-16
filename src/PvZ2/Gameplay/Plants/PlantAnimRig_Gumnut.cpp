//
//  PlantAnimRig_Gumnut.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "Plant_Gumnut.h"
#include "ReflectionBuilder.h"

/////////////// Lifecycle ///////////////

PlantAnimRig_Gumnut::PlantAnimRig_Gumnut()
{
}

PlantAnimRig_Gumnut::~PlantAnimRig_Gumnut()
{
}

/////////////// Reflection ///////////////

RT_CLASS_IMPLEMENT(PlantAnimRig_Gumnut);

void PlantAnimRig_Gumnut::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantAnimRig_Gumnut);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantAnimRig);

	REFLECTION_CLASSBUILDER_END(PlantAnimRig_Gumnut);
}

/////////////// Logic ///////////////

std::string PlantAnimRig_Gumnut::getPlantFoodMainAnimName()
{
	return m_bAvatar ? "plantfood2" : "plantfood";
}
