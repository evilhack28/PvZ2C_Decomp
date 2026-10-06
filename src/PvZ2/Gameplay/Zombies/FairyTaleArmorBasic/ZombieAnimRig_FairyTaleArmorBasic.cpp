//
//  ZombieAnimRig_FairyTaleArmorBasic.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "ZombieFairyTaleBasic.h"

ZombieAnimRig_FairyTaleArmorBasic::ZombieAnimRig_FairyTaleArmorBasic()
{
}

ZombieAnimRig_FairyTaleArmorBasic::~ZombieAnimRig_FairyTaleArmorBasic()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieAnimRig_FairyTaleArmorBasic);

void ZombieAnimRig_FairyTaleArmorBasic::SetLayerVisibilityForCurrentState()
{
	ZombieAnimRig_Basic::SetLayerVisibilityForCurrentState();
	SetLayerVisibility("_zombie_armor_hat_states", false);
}
