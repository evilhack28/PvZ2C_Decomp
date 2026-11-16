//
//  ZombieAnimRig_ZoybeanPodBasic.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "ZombieZoybeanPodBasic.h"

ZombieAnimRig_ZoybeanPodBasic::~ZombieAnimRig_ZoybeanPodBasic()
{
}

void ZombieAnimRig_ZoybeanPodBasic::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombieAnimRig_ZoybeanPodBasic);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ZombieAnimRig_Basic);

	REFLECTION_CLASSBUILDER_END(ZombieAnimRig_ZoybeanPodBasic);
}

#include "ZombieAnimRig_Basic.h"
void ZombieAnimRig_ZoybeanPodBasic::onPopAnimInitialized()
{
	 ZombieAnimRig_Basic::onPopAnimInitialized();
}
