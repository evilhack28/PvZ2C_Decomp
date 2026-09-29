//
//  ZombieAnimRig_ModernMiner.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "ZombieModernMiner.h"

ZombieAnimRig_ModernMiner::ZombieAnimRig_ModernMiner()
{
	m_hasTool = 1;
	m_underground = 0;
	m_bleeding = 0;
}

ZombieAnimRig_ModernMiner::~ZombieAnimRig_ModernMiner()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieAnimRig_ModernMiner);

void ZombieAnimRig_ModernMiner::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombieAnimRig_ModernMiner);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ZombieAnimRig_Basic);

	REFLECTION_CLASSBUILDER_END(ZombieAnimRig_ModernMiner);
}

#include "ZombieAnimRig_Basic.h"
const std::vector<std::string>& ZombieAnimRig_ModernMiner::getFlagHandLayerNames()
{
	return ZombieAnimRig_Basic::getEmptyLayerNames();
}

#include "ZombieAnimRig_Basic.h"
const std::vector<std::string>& ZombieAnimRig_ModernMiner::getNoFlagHandLayerNames()
{
	return ZombieAnimRig_Basic::getEmptyLayerNames();
}

#include "ZombieAnimRig_Basic.h"
const std::vector<std::string>& ZombieAnimRig_ModernMiner::getArmReplacementPairNames()
{
	return ZombieAnimRig_Basic::getEmptyLayerNames();
}
