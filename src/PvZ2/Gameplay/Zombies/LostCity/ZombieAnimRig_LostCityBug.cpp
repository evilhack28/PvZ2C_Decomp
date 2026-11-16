//
//  ZombieAnimRig_LostCityBug.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "ZombieLostCityBug.h"

ZombieAnimRig_LostCityBug::ZombieAnimRig_LostCityBug()
{
	m_basicHelm = (decltype(m_basicHelm))0;
	m_hasTakenCatastrophicDamage = (decltype(m_hasTakenCatastrophicDamage))0;
}

ZombieAnimRig_LostCityBug::~ZombieAnimRig_LostCityBug()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieAnimRig_LostCityBug);

void ZombieAnimRig_LostCityBug::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombieAnimRig_LostCityBug);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ZombieAnimRig);

		REFLECTION_CLASSBUILDER_FIELD(BasicHelmType, m_basicHelm);
		REFLECTION_CLASSBUILDER_FIELD(bool, m_hasTakenCatastrophicDamage);
	REFLECTION_CLASSBUILDER_END(ZombieAnimRig_LostCityBug);
}

#include "ZombieAnimRig.h"
void ZombieAnimRig_LostCityBug::onNeedsToDie()
{
	 ZombieAnimRig::setReadyToDie();
}

#include "ZombieAnimRig.h"
const std::vector<std::string>& ZombieAnimRig_LostCityBug::getHeadLayerNames()
{
	return ZombieAnimRig::getEmptyLayerNames();
}
