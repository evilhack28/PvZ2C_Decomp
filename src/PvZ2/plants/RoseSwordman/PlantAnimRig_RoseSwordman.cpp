//
//  PlantAnimRig_RoseSwordman.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "Plant_RoseSwordman.h"

PlantAnimRig_RoseSwordman::~PlantAnimRig_RoseSwordman()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantAnimRig_RoseSwordman);

void PlantAnimRig_RoseSwordman::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantAnimRig_RoseSwordman);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantAnimRig);

	REFLECTION_CLASSBUILDER_FIELD(bool, m_showSword);

	REFLECTION_CLASSBUILDER_END(PlantAnimRig_RoseSwordman);
}
