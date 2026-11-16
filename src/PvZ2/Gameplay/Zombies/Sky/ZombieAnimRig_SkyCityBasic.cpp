//
//  ZombieAnimRig_SkyCityBasic.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "ZombieAnimRig_SkyCityBasic.h"

ZombieAnimRig_SkyCityBasic::ZombieAnimRig_SkyCityBasic()
{
}

ZombieAnimRig_SkyCityBasic::~ZombieAnimRig_SkyCityBasic()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieAnimRig_SkyCityBasic);

#include "ZombieAnimRig_Basic.h"
const std::vector<std::string>& ZombieAnimRig_SkyCityBasic::getNoFlagHandLayerNames()
{
	return ZombieAnimRig_Basic::getBoxLayerNames();
}
