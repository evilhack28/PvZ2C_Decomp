//
//  GridItemZombiePortal_AnimRig.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "GridItemZombiePortal.h"

GridItemZombiePortal_AnimRig::~GridItemZombiePortal_AnimRig()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(GridItemZombiePortal_AnimRig);

void GridItemZombiePortal_AnimRig::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(GridItemZombiePortal_AnimRig);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PopAnimRig);

		REFLECTION_CLASSBUILDER_FIELD(int, m_state);
		REFLECTION_CLASSBUILDER_FIELD(std::string, m_portalType);
	REFLECTION_CLASSBUILDER_END(GridItemZombiePortal_AnimRig);
}
