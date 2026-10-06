//
//  PlantAnimRig_Cobcannon.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "Plant_Cobcannon.h"

PlantAnimRig_Cobcannon::PlantAnimRig_Cobcannon()
{
	m_mini = 0;
	m_reloading = 0;
}

PlantAnimRig_Cobcannon::~PlantAnimRig_Cobcannon()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantAnimRig_Cobcannon);

void PlantAnimRig_Cobcannon::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantAnimRig_Cobcannon);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantAnimRig);

	REFLECTION_CLASSBUILDER_END(PlantAnimRig_Cobcannon);
}
