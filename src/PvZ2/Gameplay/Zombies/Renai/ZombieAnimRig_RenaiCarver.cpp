//
//  ZombieAnimRig_RenaiCarver.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "ZombieRenaiCarver.h"

ZombieAnimRig_RenaiCarver::ZombieAnimRig_RenaiCarver()
{
}

ZombieAnimRig_RenaiCarver::~ZombieAnimRig_RenaiCarver()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieAnimRig_RenaiCarver);

void ZombieAnimRig_RenaiCarver::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombieAnimRig_RenaiCarver);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ZombieAnimRig_Imp);

	REFLECTION_CLASSBUILDER_END(ZombieAnimRig_RenaiCarver);
}

#include "ZombieAnimRig.h"
void ZombieAnimRig_RenaiCarver::onPopAnimInitialized()
{
	 ZombieAnimRig::onPopAnimInitialized();
}
