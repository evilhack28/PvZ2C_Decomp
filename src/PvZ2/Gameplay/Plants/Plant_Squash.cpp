//
//  Plant_Squash.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "Plant_Squash.h"

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantSquash);

void PlantSquash::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantSquash);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantFramework);

		REFLECTION_CLASSBUILDER_FIELD(RtWeakPtr<StandaloneEffect>, m_plantfoodEffect);
		REFLECTION_CLASSBUILDER_FIELD(RtWeakPtr<Zombie>, m_targetZombie);
		REFLECTION_CLASSBUILDER_FIELD(bool, m_bBackToStartPoint);
	REFLECTION_CLASSBUILDER_END(PlantSquash);
}

bool PlantSquash::HasGravity()
{
	return true;
}
