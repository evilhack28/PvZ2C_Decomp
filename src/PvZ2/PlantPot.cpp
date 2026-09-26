//
//  PlantPot.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "PlantPot.h"

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantPot);

void PlantPot::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantPot);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GridItem);

	REFLECTION_CLASSBUILDER_FIELD(RtWeakPtr<Image>, m_potImage);
	REFLECTION_CLASSBUILDER_FIELD(float, m_offsetY);

	REFLECTION_CLASSBUILDER_END(PlantPot);
}
