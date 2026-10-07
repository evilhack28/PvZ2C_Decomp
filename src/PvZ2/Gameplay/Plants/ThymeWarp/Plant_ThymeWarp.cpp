//
//  Plant_ThymeWarp.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "Plant_ThymeWarp.h"

PlantThymeWarp::PlantThymeWarp()
{
}

PlantThymeWarp::~PlantThymeWarp()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantThymeWarp);

void PlantThymeWarp::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantThymeWarp);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantFramework);

		REFLECTION_CLASSBUILDER_FIELD(bool, m_quickKillEnabled);
	REFLECTION_CLASSBUILDER_END(PlantThymeWarp);
}

bool PlantThymeWarp::CanBeShoveled()
{
	return false;
}

bool PlantThymeWarp::CanBeTargeted()
{
	return false;
}

void PlantThymeWarp::TakeSmashAttack(ZombiePtr i_srcZombie)
{
}

void PlantThymeWarp::quickKillZombie(RtWeakPtr<Zombie> zombie)
{
}

bool PlantThymeWarp::HasShadow()
{
	return false;
}
