//
//  Plant_Vamporcini.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "Plant_Vamporcini.h"

PlantVamporcini::~PlantVamporcini()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantVamporcini);

void PlantVamporcini::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantVamporcini);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantFramework);

		REFLECTION_CLASSBUILDER_FIELD(DamageInfo, m_deathDamageInfo);
		REFLECTION_CLASSBUILDER_FIELD(int, m_firstAttack);
		REFLECTION_CLASSBUILDER_FIELD(Rect, m_attackRect);
		REFLECTION_CLASSBUILDER_FIELD(RtWeakPtr<Shield>, m_shield);
	REFLECTION_CLASSBUILDER_END(PlantVamporcini);
}

bool PlantVamporcini::TryBlockZombossRush(Zombie* i_zomboss)
{
	return false;
}
