//
//  Plant_Chilibean_Subsystem.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "Plant_Chilibean_Subsystem.h"

PlantChilibeanSubSystem::PlantChilibeanSubSystem()
{
}

PlantChilibeanSubSystem::~PlantChilibeanSubSystem()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantChilibeanSubSystem);

void PlantChilibeanSubSystem::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombieFlatulence);
		REFLECTION_CLASSBUILDER_FIELD(int32, State);
		REFLECTION_CLASSBUILDER_FIELD(bool, Advanced);
	REFLECTION_CLASSBUILDER_END(ZombieFlatulence);

	REFLECTION_CLASSBUILDER_BEGIN(PlantChilibeanSubSystem);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GameSubSystem);

		REFLECTION_CLASSBUILDER_FIELD(std::vector<ZombieFlatulence>, m_zombieStates);
		REFLECTION_CLASSBUILDER_FIELD(float, m_DamageAmount);
	REFLECTION_CLASSBUILDER_END(PlantChilibeanSubSystem);
}

void PlantChilibeanSubSystem::onDestroy()
{
}
