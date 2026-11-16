//
//  Plant_Gumnut.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "Plant_Gumnut.h"

PlantGumnut::PlantGumnut()
{
}

PlantGumnut::~PlantGumnut()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantGumnut);

void PlantGumnut::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantGumnut);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantFramework);

	REFLECTION_CLASSBUILDER_END(PlantGumnut);
}

CollisionTypeFlags PlantGumnut::GetCollisionFlags(PlantWeapon i_plantWeapon)
{
	return COLLIDE_ALL_ZOMBIES;
}
