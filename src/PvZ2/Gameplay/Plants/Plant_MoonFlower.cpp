//
//  Plant_MoonFlower.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "Plant_MoonFlower.h"

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantMoonFlower);

void PlantMoonFlower::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantMoonFlower);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantFramework);

		REFLECTION_CLASSBUILDER_FIELD(RtWeakPtr<ComponentConditionRadius>, m_boostRadius);
		REFLECTION_CLASSBUILDER_FIELD(RtWeakPtr<MoonFlowerPoweredTilesSubsystem>, m_moonflowerSystem);
		REFLECTION_CLASSBUILDER_FIELD(bool, m_bIsShieldAlreadyShow);
	REFLECTION_CLASSBUILDER_END(PlantMoonFlower);
}
