//
//  ZombieIceAgeTroglobite.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "ZombieIceAgeTroglobite.h"

ZombieIceAgeTroglobiteProps::~ZombieIceAgeTroglobiteProps()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieIceAgeTroglobite);

void ZombieIceAgeTroglobite::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombieIceAgeTroglobite);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ZombieWithPushingAction);

		REFLECTION_CLASSBUILDER_FIELD(int, m_renderOrder);
		REFLECTION_CLASSBUILDER_FIELD(bool, m_isOnScreen);
		REFLECTION_CLASSBUILDER_FIELD(std::vector<RtWeakPtr<Zombie> >, m_iceBlockImps);
	REFLECTION_CLASSBUILDER_END(ZombieIceAgeTroglobite);
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieIceAgeTroglobiteProps);

void ZombieIceAgeTroglobiteProps::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombieIceAgeTroglobiteProps);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ZombieWithActionsProps);

		REFLECTION_CLASSBUILDER_FIELD(int32_t, NumberOfIceblocksToSpawnWith);
		REFLECTION_CLASSBUILDER_FIELD(std::string, ConditionToApply);
	REFLECTION_CLASSBUILDER_END(ZombieIceAgeTroglobiteProps);
}

void ZombieIceAgeTroglobite::drawPushRectangle(const Sexy::Graphics* i_g)
{
}
