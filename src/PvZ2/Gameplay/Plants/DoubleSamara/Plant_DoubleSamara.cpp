//
//  Plant_DoubleSamara.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "Plant_DoubleSamara.h"

PlantDoubleSamara::PlantDoubleSamara()
{
	m_bTrigger = 0;
}

PlantDoubleSamara::~PlantDoubleSamara()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantDoubleSamara);

void PlantDoubleSamara::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(CollectedZombie);
		REFLECTION_CLASSBUILDER_FIELD(RtWeakPtr<Zombie>, m_zombiePtr);
		REFLECTION_CLASSBUILDER_FIELD(SexyVector3, m_posOrgin);
		REFLECTION_CLASSBUILDER_FIELD(pvztime_t, m_timerBack);
	REFLECTION_CLASSBUILDER_END(CollectedZombie);

	REFLECTION_CLASSBUILDER_BEGIN(PlantDoubleSamara);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantFramework);

		REFLECTION_CLASSBUILDER_FIELD(std::vector<CollectedZombie>, m_collectedZombies);
		REFLECTION_CLASSBUILDER_FIELD(bool, m_bTrigger);
	REFLECTION_CLASSBUILDER_END(PlantDoubleSamara);
}

bool PlantDoubleSamara::CanBeShoveled()
{
	return false;
}

bool PlantDoubleSamara::CanBeTargeted()
{
	return false;
}

CollisionTypeFlags PlantDoubleSamara::GetCollisionFlags(PlantWeapon i_plantWeapon)
{
	return COLLIDE_ALL_ZOMBIES;
}

void PlantDoubleSamara::DoSpecial(int i_extraParam)
{
}
