//
//  Plant_BoomFlower.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "Plant_BoomFlower.h"

PlantBoomFlower::~PlantBoomFlower()
{
}

PlantTypeBoomFlower::PlantTypeBoomFlower()
{
}

PlantTypeBoomFlower::~PlantTypeBoomFlower()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantBoomFlower);

void PlantBoomFlower::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantBoomFlower);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantFramework);

		REFLECTION_CLASSBUILDER_FIELD(RtWeakPtr<BoardEntity>, m_target);
		REFLECTION_CLASSBUILDER_FIELD(pvztime_t, m_normalChargeTime);
		REFLECTION_CLASSBUILDER_FIELD(RtWeakPtr<ComponentPlantLauncher>, m_launcherComponent);
		REFLECTION_CLASSBUILDER_FIELD(RtWeakPtr<Projectile>, m_activePlantfoodProjectile);
		REFLECTION_CLASSBUILDER_FIELD(std::vector<RtWeakPtr<BoardEntity>>, m_pfTargets);
	REFLECTION_CLASSBUILDER_END(PlantBoomFlower);
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantTypeBoomFlower);

void PlantTypeBoomFlower::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantTypeBoomFlower);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantType);

	REFLECTION_CLASSBUILDER_END(PlantTypeBoomFlower);
}

bool PlantBoomFlower::CanApplyPlantfood()
{
	return true;
}

void PlantBoomFlower::SetupLevelBasedProjectileProps(const BoomFlowerProps* i_arg)
{
}

bool PlantBoomFlower::OnFiring()
{
	return true;
}
