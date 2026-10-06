//
//  Plant_CarrotMissile.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "Plant_CarrotMissile.h"

PlantCarrotMissile::PlantCarrotMissile()
{
	m_isAvatar = 0;
}

PlantCarrotMissile::~PlantCarrotMissile()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantCarrotMissile);

void PlantCarrotMissile::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantCarrotMissile);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantFramework);

		REFLECTION_CLASSBUILDER_FIELD(bool, m_isAvatar);
	REFLECTION_CLASSBUILDER_END(PlantCarrotMissile);
}

bool PlantCarrotMissile::CanBeShoveled()
{
	return true;
}

bool PlantCarrotMissile::CanApplyPlantfood()
{
	return false;
}

bool PlantCarrotMissile::HasShadow()
{
	return false;
}
