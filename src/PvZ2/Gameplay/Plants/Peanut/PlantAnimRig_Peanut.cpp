//
//  PlantAnimRig_Peanut.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "Plant_Peanut.h"

PlantAnimRig_Peanut::~PlantAnimRig_Peanut()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantAnimRig_Peanut);

void PlantAnimRig_Peanut::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantAnimRig_Peanut);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantAnimRig);

		REFLECTION_CLASSBUILDER_FIELD(int, m_shieldDamageIndex);
		REFLECTION_CLASSBUILDER_FIELD(EPeaNutAttackType, m_eAttackType);
	REFLECTION_CLASSBUILDER_END(PlantAnimRig_Peanut);
}

int PlantAnimRig_Peanut::CalcDamageStateCount()
{
	return 3;
}
