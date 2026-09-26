//
//  PlantAnimRig_MorningGlory.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "Plant_MorningGlory.h"

PlantAnimRig_MorningGlory::PlantAnimRig_MorningGlory()
{
}

PlantAnimRig_MorningGlory::~PlantAnimRig_MorningGlory()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantAnimRig_MorningGlory);

void PlantAnimRig_MorningGlory::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantAnimRig_MorningGlory);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantAnimRig);

	REFLECTION_CLASSBUILDER_FIELD(bool, m_isLv5Attack);

	REFLECTION_CLASSBUILDER_END(PlantAnimRig_MorningGlory);
}
