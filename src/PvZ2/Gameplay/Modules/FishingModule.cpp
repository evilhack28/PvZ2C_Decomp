//
//  FishingModule.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "FishingModule.h"

void FishingModule::onLevelStarted()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(FishingModule);

void FishingModule::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombieInfo);
		REFLECTION_CLASSBUILDER_FIELD(RtWeakPtr<Zombie>, m_zombiePtr);
		REFLECTION_CLASSBUILDER_FIELD(int, m_score);
	REFLECTION_CLASSBUILDER_END(ZombieInfo);

	REFLECTION_CLASSBUILDER_BEGIN(FishingModule);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(LevelModule);

		REFLECTION_CLASSBUILDER_FIELD(RtWeakPtr<Image>, m_backImage);
		REFLECTION_CLASSBUILDER_FIELD(std::vector<RtWeakPtr<SkyCannonTypeUI>>, m_CannonTypes);
		REFLECTION_CLASSBUILDER_FIELD(int32, m_fishingState);
		REFLECTION_CLASSBUILDER_FIELD(RtWeakPtr<UIWidget>, m_sunCounterUI);
		REFLECTION_CLASSBUILDER_FIELD(std::vector<ZombieInfo>, m_zombiesCache);
		REFLECTION_CLASSBUILDER_FIELD(RtWeakPtr<Effect_PlayFrame>, m_cannonEffect);
	REFLECTION_CLASSBUILDER_END(FishingModule);
}

void FishingModule::initializeModule()
{
}

bool FishingModule::onCanPreventSave()
{
	return true;
}
