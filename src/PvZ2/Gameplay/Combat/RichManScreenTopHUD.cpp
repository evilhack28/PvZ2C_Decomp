//
//  RichManScreenTopHUD.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "RichManScreenTopHUD.h"

RichManScreenTopHUD::RichManScreenTopHUD()
{
}

RichManScreenTopHUD::~RichManScreenTopHUD()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(RichManScreenTopHUD);

void RichManScreenTopHUD::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(RichManScreenTopHUD);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PVZGameStateTopHUDController);

	REFLECTION_CLASSBUILDER_END(RichManScreenTopHUD);
}

#include "UIWidget.h"
void RichManScreenTopHUD::Open()
{
	 UIWidget::ResetUI();
}
