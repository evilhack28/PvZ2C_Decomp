//
//  AdaptorPerkInfoWidget.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "AdaptorPerkInfoWidget.h"

AdaptorPerkInfoWidget::~AdaptorPerkInfoWidget()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(AdaptorPerkInfoWidget);

void AdaptorPerkInfoWidget::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(AdaptorPerkInfoWidget);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(HotUIAdaptor);

		REFLECTION_CLASSBUILDER_FIELD(RtWeakPtr<Image>, m_perkIcon);
	REFLECTION_CLASSBUILDER_END(AdaptorPerkInfoWidget);
}
