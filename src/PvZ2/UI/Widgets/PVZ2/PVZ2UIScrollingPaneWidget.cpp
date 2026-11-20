//
//  PVZ2UIScrollingPaneWidget.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-11-20.
//

#include "SexyAppFramework/Common.h"

#include "PVZ2UIButton.h"
#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PVZ2UIScrollingPaneWidget);

void PVZ2UIScrollingPaneWidget::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PVZ2UIScrollingPaneWidget);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(Sexy::Widget);

	REFLECTION_CLASSBUILDER_END(PVZ2UIScrollingPaneWidget);
}
