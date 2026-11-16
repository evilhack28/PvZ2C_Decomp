//
//  Plant_ExplodeONut.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "Plant_ExplodeONut.h"

PlantExplodeONut::PlantExplodeONut()
{
}

PlantExplodeONut::~PlantExplodeONut()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantExplodeONut);

void PlantExplodeONut::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantExplodeONut);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantFramework);

		REFLECTION_CLASSBUILDER_FIELD(RtWeakPtr<Shield>, m_shield);
		REFLECTION_CLASSBUILDER_FIELD(RtWeakPtr<ComponentDamageRadius>, m_explodeRadius);
		REFLECTION_CLASSBUILDER_FIELD(int, m_currentBeepCount);
	REFLECTION_CLASSBUILDER_END(PlantExplodeONut);
}
