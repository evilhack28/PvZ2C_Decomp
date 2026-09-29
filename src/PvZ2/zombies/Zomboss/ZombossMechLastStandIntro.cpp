//
//  ZombossMechLastStandIntro.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "ZombossMechLastStandIntro.h"

ZombossMechLastStandIntro::~ZombossMechLastStandIntro()
{
}

ZombossMechLastStandIntroProperties::ZombossMechLastStandIntroProperties()
{
}

ZombossMechLastStandIntroProperties::~ZombossMechLastStandIntroProperties()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombossMechLastStandIntro);

void ZombossMechLastStandIntro::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombossMechLastStandIntro);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(LastStandMinigameModule);

	REFLECTION_CLASSBUILDER_END(ZombossMechLastStandIntro);
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombossMechLastStandIntroProperties);

void ZombossMechLastStandIntroProperties::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombossMechLastStandIntroProperties);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(LastStandMinigameProperties);

	REFLECTION_CLASSBUILDER_END(ZombossMechLastStandIntroProperties);
}

#include "ZombossMechLastStandIntro.h"
void ZombossMechLastStandIntro::OnIntroDone()
{
	 ZombossMechLastStandIntro::startHealthMeterFill();
}
