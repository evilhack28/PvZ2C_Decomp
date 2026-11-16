//
//  ZombieAnimRig_LostCityBasic.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "ZombieLostCityBasic.h"

ZombieAnimRig_LostCityBasic::ZombieAnimRig_LostCityBasic()
{
}

ZombieAnimRig_LostCityBasic::~ZombieAnimRig_LostCityBasic()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieAnimRig_LostCityBasic);

void ZombieAnimRig_LostCityBasic::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombieAnimRig_LostCityBasic);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ZombieAnimRig_Basic);

	REFLECTION_CLASSBUILDER_END(ZombieAnimRig_LostCityBasic);
}

#include "ZombieAnimRig_Basic.h"
const std::vector<std::string>& ZombieAnimRig_LostCityBasic::getFlagHandLayerNames()
{
	return ZombieAnimRig_Basic::getEmptyLayerNames();
}

#include "ZombieAnimRig_Basic.h"
const std::vector<std::string>& ZombieAnimRig_LostCityBasic::getNoFlagHandLayerNames()
{
	return ZombieAnimRig_Basic::getEmptyLayerNames();
}
