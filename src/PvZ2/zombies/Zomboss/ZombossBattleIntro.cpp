//
//  ZombossBattleIntro.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "ZombossBattleIntro.h"

ZombossBattleIntro::~ZombossBattleIntro()
{
}

ZombossBattleIntroProperties::~ZombossBattleIntroProperties()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombossBattleIntro);

void ZombossBattleIntro::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombossBattleIntro);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(StandardLevelIntro);

	REFLECTION_CLASSBUILDER_END(ZombossBattleIntro);
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombossBattleIntroProperties);

void ZombossBattleIntroProperties::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombossBattleIntroProperties);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(StandardLevelIntroProperties);

		REFLECTION_CLASSBUILDER_FIELD(int, ZombossPhaseCount);
		REFLECTION_CLASSBUILDER_FIELD(bool, SkipShowingStreetBossBattle);
	REFLECTION_CLASSBUILDER_END(ZombossBattleIntroProperties);
}

#include "ZombossBattleIntro.h"
void ZombossBattleIntro::OnZombossIntroDone()
{
	 ZombossBattleIntro::startHealthMeterFill();
}
