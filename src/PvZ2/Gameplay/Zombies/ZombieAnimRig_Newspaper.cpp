//
//  ZombieAnimRig_Newspaper.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "ZombieModernNewspaper.h"

ZombieAnimRig_Newspaper::ZombieAnimRig_Newspaper()
{
}

ZombieAnimRig_Newspaper::~ZombieAnimRig_Newspaper()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieAnimRig_Newspaper);

void ZombieAnimRig_Newspaper::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombieAnimRig_Newspaper);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ZombieAnimRig);

		REFLECTION_CLASSBUILDER_FIELD(bool, m_hasNewspaper);
	REFLECTION_CLASSBUILDER_END(ZombieAnimRig_Newspaper);
}
