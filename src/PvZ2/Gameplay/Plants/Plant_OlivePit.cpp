//
//  Plant_OlivePit.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "Plant_OlivePit.h"

PlantOlivePit::PlantOlivePit()
{
}

PlantOlivePit::~PlantOlivePit()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantOlivePit);

void PlantOlivePit::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantOlivePit);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantFramework);

		REFLECTION_CLASSBUILDER_FIELD(std::vector<RtWeakPtr<Zombie>>, m_plantfoodZombiesToEat);
		REFLECTION_CLASSBUILDER_FIELD(CurveSequence_SexyVector3, m_zombieSwallowCurve);
		REFLECTION_CLASSBUILDER_FIELD(std::vector<CurveSequence_SexyVector3>, m_plantfoodZombieSwallowCurves);
	REFLECTION_CLASSBUILDER_END(PlantOlivePit);
}

bool PlantOlivePit::TryBlockPush()
{
	return true;
}

CollisionTypeFlags PlantOlivePit::GetCollisionFlags(PlantWeapon i_plantWeapon)
{
	return (CollisionTypeFlags)true;
}

bool PlantOlivePit::CanBeRangeTargeted()
{
	return false;
}

bool PlantOlivePit::HasShadow()
{
	return false;
}
