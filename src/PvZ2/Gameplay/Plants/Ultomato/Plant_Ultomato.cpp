//
//  Plant_Ultomato.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "Plant_Ultomato.h"

PlantUltomato::PlantUltomato()
{
}

PlantTypeUltomato::PlantTypeUltomato()
{
}

PlantTypeUltomato::~PlantTypeUltomato()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantUltomato);

void PlantUltomato::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantUltomato);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantFramework);

		REFLECTION_CLASSBUILDER_FIELD(int32, m_level);
		REFLECTION_CLASSBUILDER_FIELD(SexyVector2, m_beamTargetPositionBoardSpace);
		REFLECTION_CLASSBUILDER_FIELD(int, m_beamState);
		REFLECTION_CLASSBUILDER_FIELD(RtWeakPtr<BoardEntity>, m_beamTarget);
	REFLECTION_CLASSBUILDER_END(PlantUltomato);
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantTypeUltomato);

PlantWeapon PlantUltomato::getBaseWeapon()
{
	return (PlantWeapon)false;
}

Projectile* PlantUltomato::Fire(ZombiePtr i_arg0, int i_arg1, PlantWeapon i_arg2)
{
	return NULL;
}
