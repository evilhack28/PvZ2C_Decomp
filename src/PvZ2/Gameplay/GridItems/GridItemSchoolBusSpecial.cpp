//
//  GridItemSchoolBusSpecial.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "GridItemSchoolBus.h"

GridItemSchoolBusSpecial::~GridItemSchoolBusSpecial()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(GridItemSchoolBusSpecial);

void GridItemSchoolBusSpecial::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(GridItemSchoolBusSpecial);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GridItemSchoolBus);

		REFLECTION_CLASSBUILDER_FIELD(float, m_airbubbleHealth);
		REFLECTION_CLASSBUILDER_FIELD(pvztime_t, m_airbubbleLaunchTime);
		REFLECTION_CLASSBUILDER_FIELD(RtWeakPtr<Zombie>, m_airbubblePtr);
		REFLECTION_CLASSBUILDER_FIELD(RtWeakPtr<Plant>, m_target);
		REFLECTION_CLASSBUILDER_FIELD(int, m_previousCol);
		REFLECTION_CLASSBUILDER_FIELD(std::vector<Point>, m_throwingTargets);
	REFLECTION_CLASSBUILDER_END(GridItemSchoolBusSpecial);
}

void GridItemSchoolBusSpecial::onUpdateAttack()
{
}

bool GridItemSchoolBusSpecial::isPendingGraveAt(int i_gridX, int i_gridY)
{
	return false;
}

bool GridItemSchoolBusSpecial::isTombraiserZombieAt(int i_gridX, int i_gridY)
{
	return false;
}

#include "GridItemSchoolBus.h"
void GridItemSchoolBusSpecial::onAttack()
{
	 GridItemSchoolBusSpecial::startSpawnAnim();
}
