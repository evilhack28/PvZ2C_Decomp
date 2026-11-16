//
//  PlantAnimRig_Dartichoke.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "Plant_Dartichoke.h"

PlantAnimRig_Dartichoke::PlantAnimRig_Dartichoke()
{
	m_plant = 0;
}

PlantAnimRig_Dartichoke::~PlantAnimRig_Dartichoke()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantAnimRig_Dartichoke);

void PlantAnimRig_Dartichoke::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantAnimRig_Dartichoke);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantAnimRig);

	REFLECTION_CLASSBUILDER_END(PlantAnimRig_Dartichoke);
}
