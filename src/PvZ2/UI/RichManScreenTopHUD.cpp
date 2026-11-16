//
//  RichManScreenTopHUD.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "RichManScreenTopHUD.h"
#include "ReflectionBuilder.h"
#include "UIWidget.h"

/////////////// Lifecycle ///////////////

RichManScreenTopHUD::RichManScreenTopHUD()
{
}

RichManScreenTopHUD::~RichManScreenTopHUD()
{
}

/////////////// Reflection ///////////////

RT_CLASS_IMPLEMENT(RichManScreenTopHUD);

void RichManScreenTopHUD::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(RichManScreenTopHUD);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PVZGameStateTopHUDController);

	REFLECTION_CLASSBUILDER_END(RichManScreenTopHUD);
}

/////////////// Logic ///////////////

void RichManScreenTopHUD::Open()
{
	 UIWidget::ResetUI();
}
