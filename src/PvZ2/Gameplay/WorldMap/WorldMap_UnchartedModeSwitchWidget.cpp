//
//  WorldMap_UnchartedModeSwitchWidget.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "WorldMap_UnchartedModeSwitchWidget.h"

WorldMap_UnchartedModeSwitchWidget::~WorldMap_UnchartedModeSwitchWidget()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(WorldMap_UnchartedModeSwitchWidget);

void WorldMap_UnchartedModeSwitchWidget::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(WorldMap_UnchartedModeSwitchWidget);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(UIWidget);

	REFLECTION_CLASSBUILDER_FIELD(UIUnchartedModeNormalButton*, m_normalButton);
	REFLECTION_CLASSBUILDER_FIELD(UIUnchartedModeHardButton*, m_hardButton);

	REFLECTION_CLASSBUILDER_END(WorldMap_UnchartedModeSwitchWidget);
}
