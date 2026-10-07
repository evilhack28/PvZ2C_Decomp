//
//  ZombieAnimRig_FootballMech.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "ZombieAnimRig_Mech.h"
#include "ReflectionBuilder.h"

/////////////// Lifecycle ///////////////

ZombieAnimRig_FootballMech::ZombieAnimRig_FootballMech()
{
}

ZombieAnimRig_FootballMech::~ZombieAnimRig_FootballMech()
{
}

/////////////// Reflection ///////////////

RT_CLASS_IMPLEMENT(ZombieAnimRig_FootballMech);

void ZombieAnimRig_FootballMech::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombieAnimRig_FootballMech);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ZombieAnimRig_Mech);

	REFLECTION_CLASSBUILDER_END(ZombieAnimRig_FootballMech);
}

/////////////// Logic ///////////////

void ZombieAnimRig_FootballMech::SetDamageState(int i_damageState)
{
	SetLayerVisibility("damage1_helmet", i_damageState == 1);
	SetLayerVisibility("damage2_helmet", i_damageState == 2);
	SetLayerVisibility("damage3_helmet", i_damageState == 3);
	bool aVisible4 = i_damageState == 4;
	SetLayerVisibility("damage4_helmet", aVisible4);
	SetLayerVisibility("damage4_leg", aVisible4);
	bool aVisible5 = i_damageState == 5;
	SetLayerVisibility("damage5_helmet", aVisible5);
	SetLayerVisibility("damage5_leg", aVisible5);
	bool aVisible6 = i_damageState == 6;
	SetLayerVisibility("damage6_helmet", aVisible6);
	SetLayerVisibility("damage6_leg", aVisible6);
}
