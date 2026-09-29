//
//  HotUILabel.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "HotUILabel.h"

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(HotUILabel);

void HotUILabel::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(HotUILabel);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(HotUIWidget);

	REFLECTION_CLASSBUILDER_END(HotUILabel);
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(HotUILabelProperties);

void HotUILabel::onInitializeWidget()
{
}
