//
//  Plant_Inferno.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "Plant_Inferno.h"

PlantInferno::PlantInferno()
{
}

PlantInferno::~PlantInferno()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantInferno);

void PlantInferno::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantInferno);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantFramework);

		REFLECTION_CLASSBUILDER_FIELD(RtWeakPtr<ComponentWarmingRadius>, m_warmingRadius);
	REFLECTION_CLASSBUILDER_END(PlantInferno);
}

void PlantInferno::onAnimStoppedCallback(const std::string& i_animLabel)
{
}
