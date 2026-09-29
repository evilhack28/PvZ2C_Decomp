//
//  GridItemLava.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "Plant_LavaGuava.h"

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(GridItemLava);

void GridItemLava::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(GridItemLava);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GridItemAnimation);

		REFLECTION_CLASSBUILDER_FIELD(int, m_state);
		REFLECTION_CLASSBUILDER_FIELD(RtWeakPtr<ComponentWarmingRadius>, m_warmingRadius);
		REFLECTION_CLASSBUILDER_FIELD(bool, m_needSpawnTinyLava);
		REFLECTION_CLASSBUILDER_FIELD(std::vector<RtWeakPtr<Effect_PopAnim> >, m_cachedEffects);
		REFLECTION_CLASSBUILDER_FIELD(float, m_damagePerSecond);
	REFLECTION_CLASSBUILDER_END(GridItemLava);
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(GridItemLavaProps);

void GridItemLavaProps::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(GridItemLavaProps);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GridItemAnimationProps);

		REFLECTION_CLASSBUILDER_FIELD(std::string, PopAnim);
		REFLECTION_CLASSBUILDER_FIELD(SexyVector2, PopAnimRenderOffset);
		REFLECTION_CLASSBUILDER_FIELD(pvztime_t, Lifetime);
		REFLECTION_CLASSBUILDER_FIELD(float, DamagePerSecond);
		REFLECTION_CLASSBUILDER_FIELD(ComponentWarmingRadiusProps, WarmingRadius);
		REFLECTION_CLASSBUILDER_FIELD(std::vector<std::string>, ZombieBlacklist);
	REFLECTION_CLASSBUILDER_END(GridItemLavaProps);
}

void GridItemLava::onCauseDamage(class Zombie* i_arg)
{
}
