//
//  ZombieAnimRig_ConeMech.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "ZombieAnimRig_Mech.h"
#include "ReflectionBuilder.h"

/////////////// Lifecycle ///////////////

ZombieAnimRig_ConeMech::ZombieAnimRig_ConeMech()
{
}

ZombieAnimRig_ConeMech::~ZombieAnimRig_ConeMech()
{
}

/////////////// Reflection ///////////////

RT_CLASS_IMPLEMENT(ZombieAnimRig_ConeMech);

void ZombieAnimRig_ConeMech::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombieAnimRig_ConeMech);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ZombieAnimRig_Mech);

	REFLECTION_CLASSBUILDER_END(ZombieAnimRig_ConeMech);
}

/////////////// Logic ///////////////

void ZombieAnimRig_ConeMech::SetDamageState(int i_damageState)
{
	SetLayerVisibility("damage1_cone_main", i_damageState == 1);
	SetLayerVisibility("damage2_cone_main", i_damageState == 2);
	SetLayerVisibility("damage3_cone_main", i_damageState == 3);
	bool aVisible4 = i_damageState == 4;
	SetLayerVisibility("damage4_cone_main", aVisible4);
	SetLayerVisibility("damage4_cone_top", aVisible4);

	bool aVisible5 = i_damageState == 5;
	SetLayerVisibility("damage5_cone_main", aVisible5);
	SetLayerVisibility("damage5_cone_top", aVisible5);
	SetLayerVisibility("damage5_mouth1", aVisible5);
	SetLayerVisibility("damage5_mouth2", aVisible5);
	SetLayerVisibility("damage5_mouth3", aVisible5);

	bool aVisible6 = i_damageState == 6;
	SetLayerVisibility("damage6_cone_main", aVisible6);
	SetLayerVisibility("damage6_cone_top", aVisible6);
	SetLayerVisibility("damage6_mouth1", aVisible6);
	SetLayerVisibility("damage6_mouth2", aVisible6);
	SetLayerVisibility("damage6_mouth3", aVisible6);
}
