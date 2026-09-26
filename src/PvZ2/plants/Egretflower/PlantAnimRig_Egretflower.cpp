//
//  PlantAnimRig_Egretflower.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "Plant_Egretflower.h"

PlantAnimRig_Egretflower::~PlantAnimRig_Egretflower()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantAnimRig_Egretflower);

void PlantAnimRig_Egretflower::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantAnimRig_Egretflower);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantAnimRig);

	REFLECTION_CLASSBUILDER_FIELD(int, m_attackMode);

	REFLECTION_CLASSBUILDER_END(PlantAnimRig_Egretflower);
}

#include "PlantAnimRig.h"
void PlantAnimRig_Egretflower::onAnimStopped()
{
	 PlantAnimRig::onAnimStopped();
}

PlantAnimRig_Egretflower::PlantAnimRig_Egretflower()
{
	m_attackMode = 0;
}

void PlantAnimRig_Egretflower::SetAttackMode(int i_arg)
{
	m_attackMode = i_arg;
}
