//
//  ZombieLostCityGuide.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "ZombieLostCityGuide.h"

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieLostCityGuide);

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieLostCityGuideProps);

void ZombieLostCityGuideProps::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombieLostCityGuideProps);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ZombiePropertySheet);

	REFLECTION_CLASSBUILDER_END(ZombieLostCityGuideProps);
}

#include "Zombie.h"
void ZombieLostCityGuide::onZombieInitialize()
{
	 Zombie::onZombieInitialize();
}

#include "Zombie.h"
void ZombieLostCityGuide::onUpdate()
{
	 Zombie::onUpdate();
}
