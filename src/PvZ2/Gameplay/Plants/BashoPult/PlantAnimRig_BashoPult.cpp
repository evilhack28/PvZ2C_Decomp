//
//  PlantAnimRig_BashoPult.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "Plant_BashoPult.h"

PlantAnimRig_BashoPult::PlantAnimRig_BashoPult()
{
}

PlantAnimRig_BashoPult::~PlantAnimRig_BashoPult()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantAnimRig_BashoPult);

void PlantAnimRig_BashoPult::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantAnimRig_BashoPult);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantAnimRig);

	REFLECTION_CLASSBUILDER_END(PlantAnimRig_BashoPult);
}
