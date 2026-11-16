//
//  ZombieAnimRig_Guide.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "ZombieLostCityGuide.h"
#include "ReflectionBuilder.h"

/////////////// Lifecycle ///////////////

ZombieAnimRig_Guide::ZombieAnimRig_Guide()
{
}

ZombieAnimRig_Guide::~ZombieAnimRig_Guide()
{
}

/////////////// Reflection ///////////////

RT_CLASS_IMPLEMENT(ZombieAnimRig_Guide);

/////////////// Logic ///////////////

bool ZombieAnimRig_Guide::DoGuideAnimation(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped)
{
	AnimHandle handle = PlayAndStop("guide", SELECT_EXACT, i_onAnimStopped);
	if (handle != ANIMHANDLE_NONE)
	{
		m_state = ZOMBIEANIM_USERDEFINED;
		return true;
	}

	return false;
}
