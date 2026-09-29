//
//  Plant_Peach.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "Plant_Peach.h"

PlantPeach::PlantPeach()
{
}

PlantPeach::~PlantPeach()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantPeach);

void PlantPeach::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantPeach);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantFramework);

	REFLECTION_CLASSBUILDER_END(PlantPeach);
}

bool PlantPeach::CanApplyPlantfood()
{
	return true;
}

void PlantPeach::DoSpecial(int i_arg)
{
}

#include "PlantFramework.h"
void PlantPeach::onDestroy()
{
	 PlantFramework::onDestroy();
}
