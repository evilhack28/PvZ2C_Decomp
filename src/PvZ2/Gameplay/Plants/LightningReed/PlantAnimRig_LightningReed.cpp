//
//  PlantAnimRig_LightningReed.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "PlantAnimRig_LightningReed.h"

PlantAnimRig_LightningReed::PlantAnimRig_LightningReed()
{
}

PlantAnimRig_LightningReed::~PlantAnimRig_LightningReed()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantAnimRig_LightningReed);

bool PlantAnimRig_LightningReed::PlayAttackAnim(const std::string& i_attackAnim)
{
	AnimHandle handle = PlayAndStop(i_attackAnim);
	if (handle != -1)
	{
		m_state = PLANTANIM_ATTACK;
		return true;
	}

	return false;
}

