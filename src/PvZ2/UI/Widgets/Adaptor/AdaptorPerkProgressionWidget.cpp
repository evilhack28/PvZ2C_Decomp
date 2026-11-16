//
//  AdaptorPerkProgressionWidget.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "AdaptorPerkProgressionWidget.h"

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(AdaptorPerkProgressionWidget);

void AdaptorPerkProgressionWidget::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(AdaptorPerkProgressionWidget);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(HotUIAdaptor);

	REFLECTION_CLASSBUILDER_END(AdaptorPerkProgressionWidget);
}
