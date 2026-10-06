//
//  PlantfoodTutorialIntro.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "PlantfoodTutorialIntro.h"

PlantfoodTutorialIntro::PlantfoodTutorialIntro()
{
}

PlantfoodTutorialIntro::~PlantfoodTutorialIntro()
{
}

PlantfoodTutorialIntroProperties::PlantfoodTutorialIntroProperties()
{
}

PlantfoodTutorialIntroProperties::~PlantfoodTutorialIntroProperties()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantfoodTutorialIntro);

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantfoodTutorialIntroProperties);

void PlantfoodTutorialIntroProperties::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantfoodTutorialIntroProperties);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(StandardLevelIntroProperties);

	REFLECTION_CLASSBUILDER_END(PlantfoodTutorialIntroProperties);
}

void PlantfoodTutorialIntro::onPlantDied(Plant* i_arg)
{
}

void PlantfoodTutorialIntro::onCoinBanked(Collectable* i_arg)
{
}
