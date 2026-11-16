//
//  PlantAnimRig_WinterMelon.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "Plant_WinterMelon.h"

PlantAnimRig_WinterMelon::~PlantAnimRig_WinterMelon()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantAnimRig_WinterMelon);

void PlantAnimRig_WinterMelon::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantAnimRig_WinterMelon);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantAnimRig);

	REFLECTION_CLASSBUILDER_FIELD(std::string, m_defaultAttack);

	REFLECTION_CLASSBUILDER_END(PlantAnimRig_WinterMelon);
}
