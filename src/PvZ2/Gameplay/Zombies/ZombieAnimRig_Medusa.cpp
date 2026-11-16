//
//  ZombieAnimRig_Medusa.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "ZombieRomanMedusa.h"

ZombieAnimRig_Medusa::ZombieAnimRig_Medusa()
{
}

ZombieAnimRig_Medusa::~ZombieAnimRig_Medusa()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieAnimRig_Medusa);

void ZombieAnimRig_Medusa::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombieAnimRig_Medusa);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ZombieAnimRig_Troglobite);

	REFLECTION_CLASSBUILDER_END(ZombieAnimRig_Medusa);
}
