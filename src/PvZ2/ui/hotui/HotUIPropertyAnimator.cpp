//
//  HotUIPropertyAnimator.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "HotUIPropertyAnimator.h"

HotUIPropertyAnimator::HotUIPropertyAnimator()
{
}

HotUIPropertyAnimator::~HotUIPropertyAnimator()
{
}

HotUIPropertyAnimatorProperties::~HotUIPropertyAnimatorProperties()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(HotUIPropertyAnimator);

void HotUIPropertyAnimator::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(HotUIPropertyAnimator);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(HotUIComponent);

	REFLECTION_CLASSBUILDER_END(HotUIPropertyAnimator);
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(HotUIPropertyAnimatorProperties);
