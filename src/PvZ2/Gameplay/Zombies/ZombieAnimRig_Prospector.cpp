//
//  ZombieAnimRig_Prospector.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "ZombieAnimRig_Prospector.h"

ZombieAnimRig_Prospector::ZombieAnimRig_Prospector()
{
	m_dynamiteState = (decltype(m_dynamiteState))0;
}

ZombieAnimRig_Prospector::~ZombieAnimRig_Prospector()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieAnimRig_Prospector);

void ZombieAnimRig_Prospector::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombieAnimRig_Prospector);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ZombieAnimRig);

	REFLECTION_CLASSBUILDER_END(ZombieAnimRig_Prospector);
}
