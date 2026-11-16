//
//  PlantAnimRig_Stunion.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "Plant_Stunion.h"

PlantAnimRig_Stunion::~PlantAnimRig_Stunion()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantAnimRig_Stunion);

void PlantAnimRig_Stunion::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantAnimRig_Stunion);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantAnimRig);

	REFLECTION_CLASSBUILDER_FIELD(bool, m_advanced);

	REFLECTION_CLASSBUILDER_END(PlantAnimRig_Stunion);
}

PlantAnimRig_Stunion::PlantAnimRig_Stunion()
{
	m_advanced = 0;
}
