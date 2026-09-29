//
//  Plant_HeadbutterLettuce.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "Plant_HeadbutterLettuce.h"

PlantHeadbutterLettuce::PlantHeadbutterLettuce()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantHeadbutterLettuce);

void PlantHeadbutterLettuce::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantHeadbutterLettuce);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantFramework);

		REFLECTION_CLASSBUILDER_FIELD(std::vector<RtWeakPtr<BoardEntity>>, m_targetsAlreadyButtered);
	REFLECTION_CLASSBUILDER_END(PlantHeadbutterLettuce);
}

bool PlantHeadbutterLettuce::CanApplyPlantfood()
{
	return true;
}

void PlantHeadbutterLettuce::onAnimStoppedCallback(const std::string& i_arg)
{
}
