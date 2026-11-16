//
//  GridItemHeianBoxLevelUpAnimRig.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "GridItemHeianBox.h"

GridItemHeianBoxLevelUpAnimRig::GridItemHeianBoxLevelUpAnimRig()
{
}

GridItemHeianBoxLevelUpAnimRig::~GridItemHeianBoxLevelUpAnimRig()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(GridItemHeianBoxLevelUpAnimRig);

void GridItemHeianBoxLevelUpAnimRig::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(GridItemHeianBoxLevelUpAnimRig);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GridItemHeianBoxAnimRig);

	REFLECTION_CLASSBUILDER_END(GridItemHeianBoxLevelUpAnimRig);
}
