//
//  WhackAMoleUI.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "WhackAMoleUI.h"

void WhackAMoleUI::registerForEvents()
{
}

void WhackAMoleUI::onUpdate()
{
}

WhackAMoleUI::~WhackAMoleUI()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(WhackAMoleUI);

void WhackAMoleUI::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(WhackAMoleUI);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(UIWidget);

		REFLECTION_CLASSBUILDER_FIELD(float, m_timeRemaining);
	REFLECTION_CLASSBUILDER_END(WhackAMoleUI);
}

void WhackAMoleUI::onInitialized()
{
}

void WhackAMoleUI::onOakArrowHitted(const int i_target_type, const int i_count)
{
}

#include "UIWidget.h"
void WhackAMoleUI::onDestroy()
{
	 UIWidget::onDestroy();
}
