//
//  Plant_Pinecone.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "Plant_Pinecone.h"

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantPinecone);

void PlantPinecone::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantPinecone);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantFramework);

		REFLECTION_CLASSBUILDER_FIELD(pvztime_t, m_laserStartTime);
	REFLECTION_CLASSBUILDER_END(PlantPinecone);
}

void PlantPinecone::UpdateActions()
{
}

bool PlantPinecone::CanApplyPlantfood()
{
	return true;
}

#include "PlantFramework.h"
void PlantPinecone::PlayAttackAnimation()
{
	 PlantFramework::PlayAttackAnimation();
}
