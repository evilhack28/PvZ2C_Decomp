//
//  Plant_Torchwood.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "Plant_Torchwood.h"

PlantTorchwood::PlantTorchwood()
{
}

PlantTorchwood::~PlantTorchwood()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantTorchwood);

void PlantTorchwood::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantTorchwood);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantFramework);

		REFLECTION_CLASSBUILDER_FIELD(RtWeakPtr<ComponentWarmingRadius>, m_warmingRadius);
	REFLECTION_CLASSBUILDER_END(PlantTorchwood);
}

void PlantTorchwood::UpdateActions()
{
}
