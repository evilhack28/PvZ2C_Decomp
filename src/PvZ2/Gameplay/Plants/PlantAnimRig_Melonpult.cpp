//
//  PlantAnimRig_Melonpult.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "Plant_Melonpult.h"

PlantAnimRig_Melonpult::~PlantAnimRig_Melonpult()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantAnimRig_Melonpult);

void PlantAnimRig_Melonpult::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantAnimRig_Melonpult);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantAnimRig);

	REFLECTION_CLASSBUILDER_FIELD(std::string, m_defaultAttack);

	REFLECTION_CLASSBUILDER_END(PlantAnimRig_Melonpult);
}
