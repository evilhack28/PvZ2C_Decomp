//
//  PlantAnimRig_KiwiBeast.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "Plant_KiwiBeast.h"

PlantAnimRig_KiwiBeast::PlantAnimRig_KiwiBeast()
{
}

PlantAnimRig_KiwiBeast::~PlantAnimRig_KiwiBeast()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantAnimRig_KiwiBeast);

void PlantAnimRig_KiwiBeast::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantAnimRig_KiwiBeast);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantAnimRig);

		REFLECTION_CLASSBUILDER_FIELD(int32_t, m_growthLevel);
	REFLECTION_CLASSBUILDER_END(PlantAnimRig_KiwiBeast);
}
