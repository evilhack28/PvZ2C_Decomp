//
//  Plant_ByttneriaMeteorHammer.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "Plant_ByttneriaMeteorHammer.h"

PlantByttneriaMeteorHammer::PlantByttneriaMeteorHammer()
{
}

PlantByttneriaMeteorHammer::~PlantByttneriaMeteorHammer()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantByttneriaMeteorHammer);

void PlantByttneriaMeteorHammer::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantByttneriaMeteorHammer);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantFramework);

		REFLECTION_CLASSBUILDER_FIELD(std::vector<Point>, m_validTargetPoints);
		REFLECTION_CLASSBUILDER_FIELD(RtWeakPtr<BoardEntity>, m_chargeTarget);
	REFLECTION_CLASSBUILDER_END(PlantByttneriaMeteorHammer);
}

#include "PlantFramework.h"
void PlantByttneriaMeteorHammer::ApplyPlantfood()
{
	 PlantFramework::ApplyPlantfood();
}

void PlantByttneriaMeteorHammer::UpdatePlantfood()
{
}

bool PlantByttneriaMeteorHammer::CanApplyPlantfood()
{
	return true;
}

bool PlantByttneriaMeteorHammer::FindTargetAndFire(PlantWeapon i_arg)
{
	return false;
}
