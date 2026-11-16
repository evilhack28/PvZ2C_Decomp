//
//  ZombieAnimRig_FairyTaleArmorBasic.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "ZombieFairyTaleBasic.h"
#include "ReflectionBuilder.h"

/////////////// Lifecycle ///////////////

ZombieAnimRig_FairyTaleArmorBasic::ZombieAnimRig_FairyTaleArmorBasic()
{
}

ZombieAnimRig_FairyTaleArmorBasic::~ZombieAnimRig_FairyTaleArmorBasic()
{
}

/////////////// Reflection ///////////////

RT_CLASS_IMPLEMENT(ZombieAnimRig_FairyTaleArmorBasic);

/////////////// Accessors ///////////////

void ZombieAnimRig_FairyTaleArmorBasic::SetLayerVisibilityForCurrentState()
{
	ZombieAnimRig_Basic::SetLayerVisibilityForCurrentState();
	SetLayerVisibility("_zombie_armor_hat_states", false);
}
