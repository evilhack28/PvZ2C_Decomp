//
//  Plant_WhiteMelon.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "Plant_WhiteMelon.h"

PlantWhiteMelon::~PlantWhiteMelon()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantWhiteMelon);

void PlantWhiteMelon::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantWhiteMelon);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantFramework);

	REFLECTION_CLASSBUILDER_END(PlantWhiteMelon);
}

bool PlantWhiteMelon::HasGravity()
{
	return true;
}

bool PlantWhiteMelon::CanApplyPlantfood()
{
	return true;
}

#include "PlantFramework.h"
void PlantWhiteMelon::onDestroy()
{
	 PlantFramework::onDestroy();
}
