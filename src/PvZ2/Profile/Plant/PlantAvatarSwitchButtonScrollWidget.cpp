//
//  PlantAvatarSwitchButtonScrollWidget.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-10-18.
//

#include "SexyAppFramework/Common.h"

#include "PlantAvatarListView.h"

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantAvatarSwitchButtonScrollWidget);

void PlantAvatarSwitchButtonScrollWidget::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantAvatarSwitchButtonScrollWidget);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(Sexy::Widget);

	REFLECTION_CLASSBUILDER_END(PlantAvatarSwitchButtonScrollWidget);
}

void PlantAvatarSwitchButtonScrollWidget::ScrollTargetReached(ScrollWidget* i_arg)
{
}

void PlantAvatarSwitchButtonScrollWidget::ScrollTargetInterrupted(ScrollWidget* i_arg)
{
}
