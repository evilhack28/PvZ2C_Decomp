//
//  PlantAnimRig_Ents.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "PlantAnimRig_Ents.h"

PlantAnimRig_Ents::PlantAnimRig_Ents()
{
	m_amulet = (decltype(m_amulet))2;
	IsBreak = 0;
}

PlantAnimRig_Ents::~PlantAnimRig_Ents()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantAnimRig_Ents);

void PlantAnimRig_Ents::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantAnimRig_Ents);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantAnimRig);

	REFLECTION_CLASSBUILDER_END(PlantAnimRig_Ents);
}
