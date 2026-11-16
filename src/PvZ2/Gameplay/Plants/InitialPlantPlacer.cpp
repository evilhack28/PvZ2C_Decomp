//
//  InitialPlantPlacer.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "InitialPlantPlacer.h"

InitialPlantPlacer::InitialPlantPlacer()
{
}

InitialPlantPlacer::~InitialPlantPlacer()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(InitialPlantPlacer);

void InitialPlantPlacer::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(InitialPlantPlacer);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(LevelModule);

	REFLECTION_CLASSBUILDER_FIELD(std::vector<RtWeakPtr<Plant> >, m_plantedPlants);

	REFLECTION_CLASSBUILDER_END(InitialPlantPlacer);
}
