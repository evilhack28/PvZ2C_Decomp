//
//  PlantAnimRig_Mandrake.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "Plant_Mandrake.h"

PlantAnimRig_Mandrake::~PlantAnimRig_Mandrake()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantAnimRig_Mandrake);

void PlantAnimRig_Mandrake::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantAnimRig_Mandrake);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantAnimRig);

		REFLECTION_CLASSBUILDER_FIELD(std::string, i_idleTag);
		REFLECTION_CLASSBUILDER_FIELD(RtWeakPtr<Plant>, m_waternut);
	REFLECTION_CLASSBUILDER_END(PlantAnimRig_Mandrake);
}
