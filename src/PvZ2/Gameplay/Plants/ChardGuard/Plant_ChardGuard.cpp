//
//  Plant_ChardGuard.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "Plant_ChardGuard.h"

PlantChardGuard::PlantChardGuard()
{
	m_maxLeafCount = (decltype(m_maxLeafCount))3;
}

PlantChardGuard::~PlantChardGuard()
{
}

PlantTypeChardGuard::PlantTypeChardGuard()
{
}

PlantTypeChardGuard::~PlantTypeChardGuard()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantChardGuard);

void PlantChardGuard::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantChardGuard);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantFramework);

		REFLECTION_CLASSBUILDER_FIELD(int32, m_playingAnim);
	REFLECTION_CLASSBUILDER_END(PlantChardGuard);
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantTypeChardGuard);

bool PlantChardGuard::CanApplyPlantfood()
{
	return true;
}
