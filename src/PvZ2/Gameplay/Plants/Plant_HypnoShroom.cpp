//
//  Plant_HypnoShroom.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "Plant_HypnoShroom.h"

PlantHypnoShroom::PlantHypnoShroom()
{
}

PlantHypnoShroom::~PlantHypnoShroom()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantHypnoShroom);

void PlantHypnoShroom::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantHypnoShroom);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantFramework);

	REFLECTION_CLASSBUILDER_END(PlantHypnoShroom);
}

#include "PlantFramework.h"
void PlantHypnoShroom::Initialize()
{
	 PlantFramework::Initialize();
}

CollisionTypeFlags PlantHypnoShroom::GetCollisionFlags(PlantWeapon i_plantWeapon)
{
	return (CollisionTypeFlags)true;
}
