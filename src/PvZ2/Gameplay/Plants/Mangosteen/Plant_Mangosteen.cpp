//
//  Plant_Mangosteen.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "Plant_Mangosteen.h"

PlantMangosteen::PlantMangosteen()
{
}

PlantMangosteen::~PlantMangosteen()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantMangosteen);

void PlantMangosteen::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantMangosteen);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantFramework);

		REFLECTION_CLASSBUILDER_FIELD(MangosteenState, m_lastIdleState);
		REFLECTION_CLASSBUILDER_FIELD(int, m_attackTimes);
		REFLECTION_CLASSBUILDER_FIELD(ZombiePtr, m_target);
		REFLECTION_CLASSBUILDER_FIELD(MangosteenElectricCirclePtr, m_elecCircle);
	REFLECTION_CLASSBUILDER_END(PlantMangosteen);
}

void PlantMangosteen::DoSpecial(int i_arg)
{
}
