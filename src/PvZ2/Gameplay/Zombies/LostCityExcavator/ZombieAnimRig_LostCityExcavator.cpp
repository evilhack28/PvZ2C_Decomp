//
//  ZombieAnimRig_LostCityExcavator.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "ZombieLostCityExcavator.h"

ZombieAnimRig_LostCityExcavator::ZombieAnimRig_LostCityExcavator()
{
	m_hasShovel = 1;
}

ZombieAnimRig_LostCityExcavator::~ZombieAnimRig_LostCityExcavator()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieAnimRig_LostCityExcavator);

void ZombieAnimRig_LostCityExcavator::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombieAnimRig_LostCityExcavator);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ZombieAnimRig_Basic);

		REFLECTION_CLASSBUILDER_FIELD(bool, m_hasShovel);
	REFLECTION_CLASSBUILDER_END(ZombieAnimRig_LostCityExcavator);
}

#include "ZombieAnimRig_Basic.h"
const std::vector<std::string>& ZombieAnimRig_LostCityExcavator::getFlagHandLayerNames()
{
	return ZombieAnimRig_Basic::getEmptyLayerNames();
}

#include "ZombieAnimRig_Basic.h"
const std::vector<std::string>& ZombieAnimRig_LostCityExcavator::getNoFlagHandLayerNames()
{
	return ZombieAnimRig_Basic::getEmptyLayerNames();
}

#include "ZombieAnimRig_Basic.h"
const std::vector<std::string>& ZombieAnimRig_LostCityExcavator::getArmReplacementPairNames()
{
	return ZombieAnimRig_Basic::getEmptyLayerNames();
}
