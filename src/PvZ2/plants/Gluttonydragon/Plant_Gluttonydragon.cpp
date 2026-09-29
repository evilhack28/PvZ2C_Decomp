//
//  Plant_Gluttonydragon.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "Plant_Gluttonydragon.h"

PlantGluttonydragon::PlantGluttonydragon()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantGluttonydragon);

void PlantGluttonydragon::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantGluttonydragon);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantFramework);

		REFLECTION_CLASSBUILDER_FIELD(float, m_energyValue);
		REFLECTION_CLASSBUILDER_FIELD(GluttonydragonState, m_state);
		REFLECTION_CLASSBUILDER_FIELD(std::vector<RtWeakPtr<Zombie> >, m_suctionZombies);
	REFLECTION_CLASSBUILDER_END(PlantGluttonydragon);
}

bool PlantGluttonydragon::CanApplyPlantfood()
{
	return true;
}
