//
//  PlantAnimRig_Pineapple.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "Plant_Pineapple.h"

PlantAnimRig_Pineapple::~PlantAnimRig_Pineapple()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantAnimRig_Pineapple);

void PlantAnimRig_Pineapple::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantAnimRig_Pineapple);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantAnimRig);

		REFLECTION_CLASSBUILDER_FIELD(RtWeakPtr<RealObject>, m_ptrObject);
	REFLECTION_CLASSBUILDER_END(PlantAnimRig_Pineapple);
}
