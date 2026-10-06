//
//  PlantAnimRig_GreenTurnip.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "Plant_GreenTurnip.h"

PlantAnimRig_GreenTurnip::PlantAnimRig_GreenTurnip()
{
	m_projectileCount = 0;
}

PlantAnimRig_GreenTurnip::~PlantAnimRig_GreenTurnip()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantAnimRig_GreenTurnip);

void PlantAnimRig_GreenTurnip::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantAnimRig_GreenTurnip);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantAnimRig);

		REFLECTION_CLASSBUILDER_FIELD(int, m_projectileCount);
	REFLECTION_CLASSBUILDER_END(PlantAnimRig_GreenTurnip);
}
