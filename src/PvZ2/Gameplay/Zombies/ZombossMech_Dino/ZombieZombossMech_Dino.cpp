//
//  ZombieZombossMech_Dino.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "ZombieZombossMech_Dino.h"

ZombieZombossMechDinoProps::~ZombieZombossMechDinoProps()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieZombossMech_Dino);

void ZombieZombossMech_Dino::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombieZombossMech_Dino);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ZombieZombossMech);

	REFLECTION_CLASSBUILDER_END(ZombieZombossMech_Dino);
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieZombossMechDinoProps);

void ZombieZombossMechDinoProps::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombieZombossMechDinoProps);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ZombieZombossMechProps);

		REFLECTION_CLASSBUILDER_FIELD(Point, LaserOffset);
	REFLECTION_CLASSBUILDER_END(ZombieZombossMechDinoProps);
}

bool ZombieZombossMech_Dino::isPlantAllowedUnderZomboss(const PlantType* i_arg)
{
	return true;
}

#include "ZombieZombossMech.h"
void ZombieZombossMech_Dino::onUpdate()
{
	 ZombieZombossMech::onUpdate();
}
