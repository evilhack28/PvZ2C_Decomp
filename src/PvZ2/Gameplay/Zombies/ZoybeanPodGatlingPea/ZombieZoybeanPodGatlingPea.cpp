//
//  ZombieZoybeanPodGatlingPea.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "ZombieZoybeanPodGatlingPea.h"

ZombieZoybeanPodGatlingPea::~ZombieZoybeanPodGatlingPea()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieZoybeanPodGatlingPea);

void ZombieZoybeanPodGatlingPea::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombieZoybeanPodGatlingPea);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ZombieShooter);

		REFLECTION_CLASSBUILDER_FIELD(float, additionalDamage);
		REFLECTION_CLASSBUILDER_FIELD(RtWeakPtr<Plant>, m_instigator);
	REFLECTION_CLASSBUILDER_END(ZombieZoybeanPodGatlingPea);
}

#include "ZombieShooter.h"
void ZombieZoybeanPodGatlingPea::onZombieInitialize()
{
	 ZombieShooter::onZombieInitialize();
}
