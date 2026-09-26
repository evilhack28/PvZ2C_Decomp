//
//  PlantAnimRig_BoomFlower.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "Plant_BoomFlower.h"

PlantAnimRig_BoomFlower::~PlantAnimRig_BoomFlower()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantAnimRig_BoomFlower);

void PlantAnimRig_BoomFlower::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantAnimRig_BoomFlower);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantAnimRig);

	REFLECTION_CLASSBUILDER_FIELD(bool, m_isReadyToFire);

	REFLECTION_CLASSBUILDER_END(PlantAnimRig_BoomFlower);
}

void PlantAnimRig_BoomFlower::onPopAnimCommand(pvztime_t i_arg0, const std::string & i_arg1, const std::string & i_arg2)
{
}

#include "PlantAnimRig.h"
void PlantAnimRig_BoomFlower::onPopAnimInitialized()
{
	 PlantAnimRig::onPopAnimInitialized();
}
