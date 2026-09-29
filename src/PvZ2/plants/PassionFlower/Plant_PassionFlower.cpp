//
//  Plant_PassionFlower.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "Plant_PassionFlower.h"

PlantPassionFlower::PlantPassionFlower()
{
	m_isAvatarSecondAttack = 0;
}

PlantPassionFlower::~PlantPassionFlower()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantPassionFlower);

void PlantPassionFlower::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantPassionFlower);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantFramework);

		REFLECTION_CLASSBUILDER_FIELD(bool, m_isAvatarSecondAttack);
	REFLECTION_CLASSBUILDER_END(PlantPassionFlower);
}

void PlantPassionFlower::UpdateActions()
{
}

bool PlantPassionFlower::CanApplyPlantfood()
{
	return true;
}
