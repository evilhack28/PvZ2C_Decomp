//
//  AdaptorCarouselDotEntry.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "AdaptorCarouselDotEntry.h"

AdaptorCarouselDotEntry::AdaptorCarouselDotEntry()
{
}

AdaptorCarouselDotEntry::~AdaptorCarouselDotEntry()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(AdaptorCarouselDotEntry);

void AdaptorCarouselDotEntry::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(AdaptorCarouselDotEntry);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(HotUIAdaptor);

	REFLECTION_CLASSBUILDER_END(AdaptorCarouselDotEntry);
}

void AdaptorCarouselDotEntry::Configure(Sexy::WidgetContainer* i_arg)
{
	m_parent = i_arg;
}
