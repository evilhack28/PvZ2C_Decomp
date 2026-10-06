//
//  Plant_Peanut.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "Plant_Peanut.h"

PlantPeanut::PlantPeanut()
{
}

PlantPeanut::~PlantPeanut()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantPeanut);

void PlantPeanut::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantPeanut);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantPeashooter);

		REFLECTION_CLASSBUILDER_FIELD(float, m_shieldHealth);
	REFLECTION_CLASSBUILDER_END(PlantPeanut);
}
