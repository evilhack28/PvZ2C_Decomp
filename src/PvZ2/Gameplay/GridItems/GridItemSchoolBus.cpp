//
//  GridItemSchoolBus.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "GridItemSchoolBus.h"

GridItemSchoolBus::~GridItemSchoolBus()
{
}

GridItemSchoolBusProps::~GridItemSchoolBusProps()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(GridItemSchoolBus);

void GridItemSchoolBus::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(SchoolBusZombieDes);
		REFLECTION_CLASSBUILDER_FIELD(int, Level);
		REFLECTION_CLASSBUILDER_FIELD(std::string, TypeName);
	REFLECTION_CLASSBUILDER_END(SchoolBusZombieDes);

	REFLECTION_CLASSBUILDER_BEGIN(GriditemSchoolBusParams);
		REFLECTION_CLASSBUILDER_FIELD(std::vector<SchoolBusZombieDes>, Zombies);
	REFLECTION_CLASSBUILDER_END(GriditemSchoolBusParams);

	REFLECTION_CLASSBUILDER_BEGIN(GridItemSchoolBus);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GridItemBoardEntityConditionTarget);

		REFLECTION_CLASSBUILDER_FIELD(std::vector<SchoolBusZombieDes>, m_zombies);
		REFLECTION_CLASSBUILDER_FIELD(SexyVector3, m_brokenVelocity);
		REFLECTION_CLASSBUILDER_FIELD(int, m_distance);
	REFLECTION_CLASSBUILDER_END(GridItemSchoolBus);
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(GridItemSchoolBusProps);

void GridItemSchoolBusProps::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(GridItemSchoolBusProps);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GridItemBoardEntityConditionTargetProps);

	REFLECTION_CLASSBUILDER_END(GridItemSchoolBusProps);
}

void GridItemSchoolBus::updateOthers()
{
}

void GridItemSchoolBus::onUpdateAttack()
{
}

void GridItemSchoolBus::onAttack()
{
}

PlantingReason GridItemSchoolBus::GetCantPlantReason() const
{
	return PLANTING_NOT_ON_SCHOOLBUS;
}
