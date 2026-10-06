//
//  PlantAnimRig_Eleocurling.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "Plant_Eleocurling.h"

PlantAnimRig_Eleocurling::~PlantAnimRig_Eleocurling()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantAnimRig_Eleocurling);

void PlantAnimRig_Eleocurling::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantAnimRig_Eleocurling);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantAnimRig);

	REFLECTION_CLASSBUILDER_FIELD(std::string, m_idleTag);
	REFLECTION_CLASSBUILDER_FIELD(RtWeakPtr<Plant>, m_waternut);

	REFLECTION_CLASSBUILDER_END(PlantAnimRig_Eleocurling);
}
