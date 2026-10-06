//
//  AdaptorPerkLibraryWidget.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "AdaptorPerkLibraryWidget.h"

AdaptorPerkLibraryWidget::AdaptorPerkLibraryWidget()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(AdaptorPerkLibraryWidget);

void AdaptorPerkLibraryWidget::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(AdaptorPerkLibraryWidget);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(HotUIAdaptor);

	REFLECTION_CLASSBUILDER_END(AdaptorPerkLibraryWidget);
}

#include "AdaptorPerkLibraryWidget.h"
void AdaptorPerkLibraryWidget::onLinkToUIViewCreated()
{
	 AdaptorPerkLibraryWidget::createPerkScrollList();
}
