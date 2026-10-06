//
//  Plant_HeathSeeker.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "Plant_HeathSeeker.h"

PlantHeathSeeker::PlantHeathSeeker()
{
	m_projectileStarted = 0;
	m_pfShotIndex = 0;
	m_geneDoubleProjectile = 0;
}

PlantHeathSeeker::~PlantHeathSeeker()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantHeathSeeker);

void PlantHeathSeeker::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantHeathSeeker);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantFramework);

		REFLECTION_CLASSBUILDER_FIELD(std::vector<RtWeakPtr<BoardEntity>>, m_pfTargets);
		REFLECTION_CLASSBUILDER_FIELD(bool, m_projectileStarted);
		REFLECTION_CLASSBUILDER_FIELD(float, m_nextProjectileTime);
		REFLECTION_CLASSBUILDER_FIELD(int, m_pfShotIndex);
	REFLECTION_CLASSBUILDER_END(PlantHeathSeeker);
}

bool PlantHeathSeeker::CanBeShoveled()
{
	return false;
}

bool PlantHeathSeeker::CanBeTargeted()
{
	return false;
}

Projectile* PlantHeathSeeker::Fire(Zombie* i_arg0, PlantWeapon i_arg1)
{
	return NULL;
}
