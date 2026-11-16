//
//  PlantAnimRig_Bonkchoy.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "PlantAnimRig_Bonkchoy.h"

PlantAnimRig_Bonkchoy::PlantAnimRig_Bonkchoy()
{
}

PlantAnimRig_Bonkchoy::~PlantAnimRig_Bonkchoy()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantAnimRig_Bonkchoy);

void PlantAnimRig_Bonkchoy::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantAnimRig_Bonkchoy);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantAnimRig);

		REFLECTION_CLASSBUILDER_FIELD(std::string, m_lastUsedIdleAnim);
	REFLECTION_CLASSBUILDER_END(PlantAnimRig_Bonkchoy);
}
