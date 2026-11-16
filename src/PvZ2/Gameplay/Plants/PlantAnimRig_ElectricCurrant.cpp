//
//  PlantAnimRig_ElectricCurrant.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "Plant_ElectricCurrant.h"

PlantAnimRig_ElectricCurrant::PlantAnimRig_ElectricCurrant()
{
	m_isLevelFiveAttack = 0;
}

PlantAnimRig_ElectricCurrant::~PlantAnimRig_ElectricCurrant()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantAnimRig_ElectricCurrant);

void PlantAnimRig_ElectricCurrant::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantAnimRig_ElectricCurrant);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantAnimRig);

		REFLECTION_CLASSBUILDER_FIELD(bool, m_isLevelFiveAttack);
	REFLECTION_CLASSBUILDER_END(PlantAnimRig_ElectricCurrant);
}
