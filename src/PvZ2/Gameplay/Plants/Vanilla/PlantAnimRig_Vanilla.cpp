//
//  PlantAnimRig_Vanilla.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "Plant_Vanilla.h"

PlantAnimRig_Vanilla::~PlantAnimRig_Vanilla()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantAnimRig_Vanilla);

void PlantAnimRig_Vanilla::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantAnimRig_Vanilla);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantAnimRig);

		REFLECTION_CLASSBUILDER_FIELD(RtWeakPtr<class Plant>, m_plant);
		REFLECTION_CLASSBUILDER_FIELD(bool, m_bLevel5Triggled);
	REFLECTION_CLASSBUILDER_END(PlantAnimRig_Vanilla);
}
