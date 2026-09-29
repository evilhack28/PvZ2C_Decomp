//
//  GridItemAcid.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "Artifact.h"

GridItemAcid::~GridItemAcid()
{
}

GridItemAcidProps::~GridItemAcidProps()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(GridItemAcid);

void GridItemAcid::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(GridItemAcid);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GridItemAnimation);

		REFLECTION_CLASSBUILDER_FIELD(int, m_state);
		REFLECTION_CLASSBUILDER_FIELD(RtWeakPtr<Zombie>, m_zombieToEat);
	REFLECTION_CLASSBUILDER_END(GridItemAcid);
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(GridItemAcidProps);

void GridItemAcidProps::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(GridItemAcidProps);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GridItemAnimationProps);

	REFLECTION_CLASSBUILDER_END(GridItemAcidProps);
}

void GridItemAcid::ResetTimer()
{
}
