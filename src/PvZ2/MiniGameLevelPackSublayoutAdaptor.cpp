//
//  MiniGameLevelPackSublayoutAdaptor.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "MiniGameLevelPackSublayoutAdaptor.h"

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(MiniGameLevelPackSublayoutAdaptor);

void MiniGameLevelPackSublayoutAdaptor::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(MiniGameLevelPackSublayoutAdaptor);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(HotUIAdaptor);

	REFLECTION_CLASSBUILDER_END(MiniGameLevelPackSublayoutAdaptor);
}

void MiniGameLevelPackSublayoutAdaptor::ButtonPress(int i_arg)
{
}
