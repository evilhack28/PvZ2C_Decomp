//
//  HotUIAnim.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "HotUIAnim.h"

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(HotUIAnimProperties);

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(HotUIAnim);

void HotUIAnim::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(HotUIAnim);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(HotUIWidget);

	REFLECTION_CLASSBUILDER_END(HotUIAnim);
}

#include "HotUIAnim.h"
void HotUIAnim::onLayoutFinalized()
{
	 HotUIAnim::layoutAnim();
}
