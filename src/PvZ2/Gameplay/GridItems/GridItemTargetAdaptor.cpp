//
//  GridItemTargetAdaptor.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "CardTarget.h"

GridItemTargetAdaptor::GridItemTargetAdaptor()
{
}

GridItemTargetAdaptor::~GridItemTargetAdaptor()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(GridItemTargetAdaptor);

void GridItemTargetAdaptor::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(GridItemTargetAdaptor);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GridTargetAdaptor);

	REFLECTION_CLASSBUILDER_END(GridItemTargetAdaptor);
}
