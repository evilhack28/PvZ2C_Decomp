//
//  Plant_Potatomine.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "Plant_Potatomine.h"

PlantPotatomine::PlantPotatomine()
{
}

PlantPotatomine::~PlantPotatomine()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantPotatomine);

void PlantPotatomine::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantPotatomine);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantFramework);

		REFLECTION_CLASSBUILDER_FIELD(RtWeakPtr<ComponentDamageRadius>, m_explodeRadius);
	REFLECTION_CLASSBUILDER_END(PlantPotatomine);
}

void PlantPotatomine::onSetDuplicate(bool i_arg)
{
}
