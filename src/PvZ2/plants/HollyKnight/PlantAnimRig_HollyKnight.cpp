//
//  PlantAnimRig_HollyKnight.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "Plant_HollyKnight.h"

PlantAnimRig_HollyKnight::~PlantAnimRig_HollyKnight()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantAnimRig_HollyKnight);

void PlantAnimRig_HollyKnight::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantAnimRig_HollyKnight);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantAnimRig);

	REFLECTION_CLASSBUILDER_FIELD(int, m_numDamageStates);

	REFLECTION_CLASSBUILDER_END(PlantAnimRig_HollyKnight);
}

void PlantAnimRig_HollyKnight::onPopAnimCommand(pvztime_t i_arg0, const std::string & i_arg1, const std::string & i_arg2)
{
}

#include "PlantAnimRig.h"
void PlantAnimRig_HollyKnight::onPopAnimInitialized()
{
	 PlantAnimRig::onPopAnimInitialized();
}
