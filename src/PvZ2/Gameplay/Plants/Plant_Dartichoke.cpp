//
//  Plant_Dartichoke.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "Plant_Dartichoke.h"

PlantDartichoke::~PlantDartichoke()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantDartichoke);

void PlantDartichoke::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantDartichoke);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantFramework);

		REFLECTION_CLASSBUILDER_FIELD(std::vector<RtWeakPtr<BoardEntity>>, m_pfTargets);
		REFLECTION_CLASSBUILDER_FIELD(float, m_mainAttackRefreshTime);
	REFLECTION_CLASSBUILDER_END(PlantDartichoke);
}

#include "Plant_Dartichoke.h"
void PlantDartichoke::PostInitialize()
{
	 PlantDartichoke::updateAmmo();
}

bool PlantDartichoke::CanApplyPlantfood()
{
	return true;
}

BoardEntityTypeFlag PlantDartichoke::GetTargetEntityTypesForWeapon(PlantWeapon i_plantWeapon)
{
	return ENTITYTYPE_ZOMBIE;
}
