//
//  Plant_Buttercup.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "Plant_Buttercup.h"

PlantButtercup::PlantButtercup()
{
	m_plantNextFortifyAttack = 0;
}

PlantButtercup::~PlantButtercup()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantButtercup);

void PlantButtercup::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantButtercup);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantFramework);

		REFLECTION_CLASSBUILDER_FIELD(bool, m_plantNextFortifyAttack);
	REFLECTION_CLASSBUILDER_END(PlantButtercup);
}

bool PlantButtercup::CanApplyPlantfood()
{
	return true;
}

void PlantButtercup::onUseSpecialAnimCommand(pvztime_t i_arg)
{
}
