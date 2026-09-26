//
//  GridItemEggAnimRig.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "GridItemEgg.h"

GridItemEggAnimRig::~GridItemEggAnimRig()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(GridItemEggAnimRig);

void GridItemEggAnimRig::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(GridItemEggAnimRig);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PopAnimRig);

	REFLECTION_CLASSBUILDER_FIELD(int, m_damagePhase);
	REFLECTION_CLASSBUILDER_FIELD(std::string, m_idleAnimName);

	REFLECTION_CLASSBUILDER_END(GridItemEggAnimRig);
}

void GridItemEggAnimRig::PlayRoll(PopAnimRig::AnimStoppedReflectionDelegate i_arg)
{
}
