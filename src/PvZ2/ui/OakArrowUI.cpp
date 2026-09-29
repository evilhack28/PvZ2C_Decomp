//
//  OakArrowUI.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "OakArrowUI.h"

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(OakArrowUI);

void OakArrowUI::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(OakArrowUI);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(UIWidget);

		REFLECTION_CLASSBUILDER_FIELD(float, m_timeRemaining);
	REFLECTION_CLASSBUILDER_END(OakArrowUI);
}

void OakArrowUI::onInitialized()
{
}

#include "UIWidget.h"
void OakArrowUI::onDestroy()
{
	 UIWidget::onDestroy();
}
