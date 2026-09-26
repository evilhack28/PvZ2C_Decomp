//
//  GridItemVaseAnimRig.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "GridItemVase.h"

GridItemVaseAnimRig::~GridItemVaseAnimRig()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(GridItemVaseAnimRig);

void GridItemVaseAnimRig::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(GridItemVaseAnimRig);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PopAnimRig);

	REFLECTION_CLASSBUILDER_FIELD(bool, m_revealed);

	REFLECTION_CLASSBUILDER_END(GridItemVaseAnimRig);
}

#include "GridItemVase.h"
void GridItemVaseAnimRig::onDropCompleted(const std::string& i_arg)
{
	 GridItemVaseAnimRig::PlayIdle();
}
