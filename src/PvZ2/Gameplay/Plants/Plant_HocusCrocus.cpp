//
//  Plant_HocusCrocus.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "Plant_HocusCrocus.h"

PlantHocusCrocus::PlantHocusCrocus()
{
}

PlantHocusCrocus::~PlantHocusCrocus()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantHocusCrocus);

void PlantHocusCrocus::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantHocusCrocus);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantFramework);

		REFLECTION_CLASSBUILDER_FIELD(std::vector<RtWeakPtr<Zombie>>, m_warpingZombies);
		REFLECTION_CLASSBUILDER_FIELD(float, m_nextTeleportTime);
		REFLECTION_CLASSBUILDER_FIELD(int, m_fireTimes);
		REFLECTION_CLASSBUILDER_FIELD(bool, m_isRayPlus);
	REFLECTION_CLASSBUILDER_END(PlantHocusCrocus);
}
