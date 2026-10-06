//
//  PlantfoodPurchaseTutorialIntro.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "PlantfoodPurchaseTutorialIntro.h"

PlantfoodPurchaseTutorialIntro::PlantfoodPurchaseTutorialIntro()
{
}

PlantfoodPurchaseTutorialIntro::~PlantfoodPurchaseTutorialIntro()
{
}

PlantfoodPurchaseTutorialIntroProperties::PlantfoodPurchaseTutorialIntroProperties()
{
}

PlantfoodPurchaseTutorialIntroProperties::~PlantfoodPurchaseTutorialIntroProperties()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantfoodPurchaseTutorialIntro);

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantfoodPurchaseTutorialIntroProperties);

void PlantfoodPurchaseTutorialIntroProperties::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantfoodPurchaseTutorialIntroProperties);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PowerupCukeTutorialIntroProperties);

	REFLECTION_CLASSBUILDER_END(PlantfoodPurchaseTutorialIntroProperties);
}

void PlantfoodPurchaseTutorialIntro::startIntro()
{
}

void PlantfoodPurchaseTutorialIntro::enterTutorial()
{
}

bool PlantfoodPurchaseTutorialIntro::needCukeTutorial()
{
	return true;
}
