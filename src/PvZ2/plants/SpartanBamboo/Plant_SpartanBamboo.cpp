//
//  Plant_SpartanBamboo.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "Plant_BambooSpartan.h"

PlantSpartanBamboo::PlantSpartanBamboo()
{
}

PlantSpartanBamboo::~PlantSpartanBamboo()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantSpartanBamboo);

void PlantSpartanBamboo::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantSpartanBamboo);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantFramework);

		REFLECTION_CLASSBUILDER_FIELD(RtWeakPtr<Shield>, m_shield);
		REFLECTION_CLASSBUILDER_FIELD(bool, m_shieldBroken);
	REFLECTION_CLASSBUILDER_END(PlantSpartanBamboo);
}

#include "Plant_BambooSpartan.h"
bool PlantSpartanBamboo::CanBeHealed()
{
	return PlantSpartanBamboo::HasShield();
}

int PlantSpartanBamboo::SearchLRPlant(std::vector<RtWeakPtr<Plant>>& i_arg)
{
	return false;
}

int PlantSpartanBamboo::SearchUDPlant(std::vector<RtWeakPtr<Plant>>& i_arg)
{
	return false;
}

void PlantSpartanBamboo::onEndCondition(PlantConditions i_arg)
{
}

bool PlantSpartanBamboo::CanApplyPlantfood()
{
	return true;
}

bool PlantSpartanBamboo::FindTargetAndFire(PlantWeapon i_arg)
{
	return false;
}

void PlantSpartanBamboo::tryKnockbackZombie(Zombie* i_arg)
{
}

void PlantSpartanBamboo::onAnimStoppedCallback(const std::string& i_arg)
{
}

Projectile * PlantSpartanBamboo::Fire(ZombiePtr i_arg0, int i_arg1, PlantWeapon i_arg2)
{
	return NULL;
}
