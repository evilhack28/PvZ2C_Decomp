//
//  Plant_ShadowShroom.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "Plant_ShadowShroom.h"

PlantShadowShroom::PlantShadowShroom()
{
}

PlantShadowShroom::~PlantShadowShroom()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantShadowShroom);

void PlantShadowShroom::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantShadowShroom);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantFramework);

	REFLECTION_CLASSBUILDER_END(PlantShadowShroom);
}

#include "PlantFramework.h"
void PlantShadowShroom::Initialize()
{
	 PlantFramework::Initialize();
}

CollisionTypeFlags PlantShadowShroom::GetCollisionFlags(PlantWeapon i_arg)
{
	return (CollisionTypeFlags)true;
}
