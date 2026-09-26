//
//  PlantAnimRig_PhatBeet.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "Plant_PhatBeet.h"

PlantAnimRig_PhatBeet::~PlantAnimRig_PhatBeet()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantAnimRig_PhatBeet);

void PlantAnimRig_PhatBeet::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantAnimRig_PhatBeet);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantAnimRig);

	REFLECTION_CLASSBUILDER_FIELD(std::string, m_attackTag);

	REFLECTION_CLASSBUILDER_END(PlantAnimRig_PhatBeet);
}
