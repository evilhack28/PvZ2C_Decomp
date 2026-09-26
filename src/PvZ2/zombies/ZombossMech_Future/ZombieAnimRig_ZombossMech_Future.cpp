//
//  ZombieAnimRig_ZombossMech_Future.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "ZombieAnimRig_ZombossMech_Future.h"

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieAnimRig_ZombossMech_Future);

void ZombieAnimRig_ZombossMech_Future::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombieAnimRig_ZombossMech_Future);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ZombieAnimRig_ZombossMech);

	REFLECTION_CLASSBUILDER_END(ZombieAnimRig_ZombossMech_Future);
}

ZombieAnimRig_ZombossMech_Future::ZombieAnimRig_ZombossMech_Future()
{
	m_queuedTileClass = (PowerTileClass)-1;
}

void ZombieAnimRig_ZombossMech_Future::SetRocketStartAnimFromTileType(PowerTileClass i_class)
{
	m_queuedTileClass = i_class;
}

const char* ZombieAnimRig_ZombossMech_Future::getRocketStartAnimName() const
{
	switch ((int)m_queuedTileClass)
	{
	case 0:
		return "linktile1_start";
	case 1:
		return "linktile2_start";
	case 2:
		return "linktile3_start";
	case 3:
		return "linktile4_start";
	case 4:
		return "linktile5_start";
	case -1:
		return ZombieAnimRig_ZombossMech::getRocketStartAnimName();
	default:
		return ZombieAnimRig_ZombossMech::getRocketStartAnimName();
	}
}

