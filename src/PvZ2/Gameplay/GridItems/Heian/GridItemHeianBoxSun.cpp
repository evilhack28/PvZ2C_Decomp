//
//  GridItemHeianBoxSun.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "GridItemHeianBox.h"

GridItemHeianBoxSun::GridItemHeianBoxSun()
{
}

GridItemHeianBoxSun::~GridItemHeianBoxSun()
{
}

GridItemHeianBoxSunProps::~GridItemHeianBoxSunProps()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(GridItemHeianBoxSun);

void GridItemHeianBoxSun::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(GridItemHeianBoxSun);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GridItemHeianBox);

	REFLECTION_CLASSBUILDER_END(GridItemHeianBoxSun);
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(GridItemHeianBoxSunProps);

void GridItemHeianBoxSunProps::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(GridItemHeianBoxSunProps);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GridItemHeianBoxProps);

		REFLECTION_CLASSBUILDER_FIELD(float, ReturnFactor);
	REFLECTION_CLASSBUILDER_END(GridItemHeianBoxSunProps);
}
