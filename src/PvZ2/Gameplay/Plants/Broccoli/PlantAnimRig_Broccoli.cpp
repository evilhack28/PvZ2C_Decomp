//
//  PlantAnimRig_Broccoli.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "PlantAnimRig_Broccoli.h"

int PlantAnimRig_Broccoli::CalcDamageStateCount()
{
	return true;
}

PlantAnimRig_Broccoli::PlantAnimRig_Broccoli()
{
}

PlantAnimRig_Broccoli::~PlantAnimRig_Broccoli()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantAnimRig_Broccoli);

void PlantAnimRig_Broccoli::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantAnimRig_Broccoli);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantAnimRig);

		REFLECTION_CLASSBUILDER_FIELD(std::string, m_lastUsedIdleAnim);
	REFLECTION_CLASSBUILDER_END(PlantAnimRig_Broccoli);
}
