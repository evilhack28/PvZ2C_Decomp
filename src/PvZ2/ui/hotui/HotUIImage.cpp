//
//  HotUIImage.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "HotUIImage.h"

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(HotUIImage);

void HotUIImage::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(HotUIImage);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(HotUIWidget);

	REFLECTION_CLASSBUILDER_END(HotUIImage);
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(HotUIImageProperties);
