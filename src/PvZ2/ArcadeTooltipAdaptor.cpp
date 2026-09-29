//
//  ArcadeTooltipAdaptor.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "ArcadeTooltipAdaptor.h"

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ArcadeTooltipAdaptor);

void ArcadeTooltipAdaptor::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ArcadeTooltipAdaptor);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(HotUIAdaptor);

	REFLECTION_CLASSBUILDER_END(ArcadeTooltipAdaptor);
}

#include "HotUIAdaptor.h"
void ArcadeTooltipAdaptor::onAnyTouch()
{
	 HotUIAdaptor::RemoveAndDeleteWidget();
}
