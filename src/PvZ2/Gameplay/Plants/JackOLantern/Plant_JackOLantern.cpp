//
//  Plant_JackOLantern.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "Plant_JackOLantern.h"

PlantJackOLantern::~PlantJackOLantern()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantJackOLantern);

void PlantJackOLantern::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantJackOLantern);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantFramework);

		REFLECTION_CLASSBUILDER_FIELD(int, m_flameState);
		REFLECTION_CLASSBUILDER_FIELD(std::vector<RtWeakPtr<Effect_PopAnim>>, m_flameEffects);
		REFLECTION_CLASSBUILDER_FIELD(RtWeakPtr<ComponentWarmingRadius>, m_warmingRadius);
		REFLECTION_CLASSBUILDER_FIELD(bool, m_showPersistentFlame);
		REFLECTION_CLASSBUILDER_FIELD(RtWeakPtr<Projectile>, m_ghostLantern);
	REFLECTION_CLASSBUILDER_END(PlantJackOLantern);
}

bool PlantJackOLantern::CanApplyPlantfood()
{
	return true;
}

#include "Plant_JackOLantern.h"
void PlantJackOLantern::UpdateUnconditionally()
{
	 PlantJackOLantern::updateFlameIndicator();
}
