//
//  PlantAnimRig_Vamporcini.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "Plant_Vamporcini.h"

PlantAnimRig_Vamporcini::PlantAnimRig_Vamporcini()
{
	m_healthDrained = 0;
	m_Shield = 0;
	m_avatar = 0;
}

PlantAnimRig_Vamporcini::~PlantAnimRig_Vamporcini()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantAnimRig_Vamporcini);

void PlantAnimRig_Vamporcini::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantAnimRig_Vamporcini);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantAnimRig_Shielded);

		REFLECTION_CLASSBUILDER_FIELD(bool, m_healthDrained);
	REFLECTION_CLASSBUILDER_END(PlantAnimRig_Vamporcini);
}
