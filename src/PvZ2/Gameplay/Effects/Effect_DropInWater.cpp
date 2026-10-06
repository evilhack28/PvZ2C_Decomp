//
//  Effect_DropInWater.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "Plant_LotusShower.h"

Effect_DropInWater::Effect_DropInWater()
{
}

Effect_DropInWater::~Effect_DropInWater()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(Effect_DropInWater);

void Effect_DropInWater::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(Effect_DropInWater);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(Effect_PopAnim);

	REFLECTION_CLASSBUILDER_FIELD(RtWeakPtr<Plant>, m_ptrPlantLotusShower);
	REFLECTION_CLASSBUILDER_FIELD(bool, m_bPlantFood);

	REFLECTION_CLASSBUILDER_END(Effect_DropInWater);
}
