//
//  PlantAnimRig_Lemon.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "Plant_Lemon.h"

PlantAnimRig_Lemon::PlantAnimRig_Lemon()
{
}

PlantAnimRig_Lemon::~PlantAnimRig_Lemon()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantAnimRig_Lemon);

void PlantAnimRig_Lemon::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantAnimRig_Lemon);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantAnimRig);

	REFLECTION_CLASSBUILDER_END(PlantAnimRig_Lemon);
}

void PlantAnimRig_Lemon::setIdleState(int i_idleState)
{
	m_idleState = i_idleState;
}

void PlantAnimRig_Lemon::setAttackState(int i_attackState)
{
	m_attackState = i_attackState;
}
