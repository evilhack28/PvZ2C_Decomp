//
//  PlantAnimRig_Saucer.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "Plant_Saucer.h"

PlantAnimRig_Saucer::~PlantAnimRig_Saucer()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantAnimRig_Saucer);

void PlantAnimRig_Saucer::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantAnimRig_Saucer);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantAnimRig);

	REFLECTION_CLASSBUILDER_FIELD(RtWeakPtr<BoardEntity>, m_ptrSaucer);

	REFLECTION_CLASSBUILDER_END(PlantAnimRig_Saucer);
}
