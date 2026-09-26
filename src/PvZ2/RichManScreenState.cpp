//
//  RichManScreenState.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "RichManScreenState.h"

RichManScreenState::RichManScreenState()
{
}

RichManScreenState::~RichManScreenState()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(RichManScreenState);

void RichManScreenState::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(RichManScreenState);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PVZHotUIGameState);

	REFLECTION_CLASSBUILDER_END(RichManScreenState);
}

#include "RichManScreen.h"
RtClass* RichManScreenState::getHotUIAdaptorClass()
{
	return AdaptorRichManScreen::StaticGetClass();
}

#include "RichManScreenTopHUD.h"
RtClass* RichManScreenState::getTopHudControllerClass()
{
	return RichManScreenTopHUD::StaticGetClass();
}
