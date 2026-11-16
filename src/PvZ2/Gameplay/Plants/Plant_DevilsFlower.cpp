//
//  Plant_DevilsFlower.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "Plant_DevilsFlower.h"

PlantDevilsFlower::PlantDevilsFlower()
{
}

PlantDevilsFlower::~PlantDevilsFlower()
{
}

PlantTypeDevilsFlower::PlantTypeDevilsFlower()
{
}

PlantTypeDevilsFlower::~PlantTypeDevilsFlower()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantDevilsFlower);

void PlantDevilsFlower::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantDevilsFlower);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantFramework);

		REFLECTION_CLASSBUILDER_FIELD(RtWeakPtr<AddCthulhuEnergyEffect>, m_darkEffect);
		REFLECTION_CLASSBUILDER_FIELD(bool, m_isLv5);
	REFLECTION_CLASSBUILDER_END(PlantDevilsFlower);
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantTypeDevilsFlower);

void PlantDevilsFlower::OnPlantMoving(Plant* i_plant, Point& i_targetGridLocation)
{
}

#include "PlantFramework.h"
void PlantDevilsFlower::ApplyPlantfood()
{
	 PlantFramework::ApplyPlantfood();
}

bool PlantDevilsFlower::CanApplyPlantfood()
{
	return true;
}

BoardEntityTypeFlag PlantDevilsFlower::GetTargetEntityTypesForWeapon(PlantWeapon i_plantWeapon)
{
	return ENTITYTYPE_ZOMBIE;
}
