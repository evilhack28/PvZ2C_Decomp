//
//  Plant_Sarracenia.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "Plant_Sarracenia.h"

PlantSarracenia::PlantSarracenia()
{
	m_doPetrifiLevel = 0;
}

PlantSarracenia::~PlantSarracenia()
{
}

PlantSarraceniaProps::~PlantSarraceniaProps()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantSarracenia);

void PlantSarracenia::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantSarracenia);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantFramework);

		REFLECTION_CLASSBUILDER_FIELD(pvztime_t, m_specialStatusStartTime);
		REFLECTION_CLASSBUILDER_FIELD(Rect, m_collisionRect);
	REFLECTION_CLASSBUILDER_END(PlantSarracenia);
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantSarraceniaProps);

void PlantSarraceniaProps::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantSarraceniaProps);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantPropertySheet);

		REFLECTION_CLASSBUILDER_FIELD(int, AvatarPlantFoodPlayCount);
	REFLECTION_CLASSBUILDER_END(PlantSarraceniaProps);
}

#include "PlantFramework.h"
void PlantSarracenia::ApplyPlantfood()
{
	 PlantFramework::ApplyPlantfood();
}

bool PlantSarracenia::CanApplyPlantfood()
{
	return true;
}

BoardEntityTypeFlag PlantSarracenia::GetTargetEntityTypesForWeapon(PlantWeapon i_arg)
{
	return (BoardEntityTypeFlag)2;
}
