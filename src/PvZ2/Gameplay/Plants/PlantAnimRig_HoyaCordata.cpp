//
//  PlantAnimRig_HoyaCordata.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "Plant_HoyaCordata.h"

PlantAnimRig_HoyaCordata::~PlantAnimRig_HoyaCordata()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantAnimRig_HoyaCordata);

void PlantAnimRig_HoyaCordata::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantAnimRig_HoyaCordata);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantAnimRig);

	REFLECTION_CLASSBUILDER_FIELD(std::string, i_idleTag);

	REFLECTION_CLASSBUILDER_END(PlantAnimRig_HoyaCordata);
}
