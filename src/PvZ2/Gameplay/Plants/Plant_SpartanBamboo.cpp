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

int PlantSpartanBamboo::SearchLRPlant(std::vector<RtWeakPtr<Plant>>& i_plants)
{
	return false;
}

int PlantSpartanBamboo::SearchUDPlant(std::vector<RtWeakPtr<Plant>>& i_plants)
{
	return false;
}

void PlantSpartanBamboo::onEndCondition(PlantConditions i_condition)
{
}

bool PlantSpartanBamboo::CanApplyPlantfood()
{
	return true;
}

bool PlantSpartanBamboo::FindTargetAndFire(PlantWeapon i_plantWeapon)
{
	return false;
}

void PlantSpartanBamboo::tryKnockbackZombie(Zombie* i_zombie)
{
}

void PlantSpartanBamboo::onAnimStoppedCallback(const std::string& i_labelname)
{
}

Projectile * PlantSpartanBamboo::Fire(ZombiePtr i_targetZombie, int i_row, PlantWeapon i_plantWeapon)
{
	return NULL;
}
