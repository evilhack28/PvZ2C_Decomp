//
//  HotUIMultiImage.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "HotUIMultiImage.h"

HotUIMultiImageProperties::~HotUIMultiImageProperties()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(HotUIMultiImage);

void HotUIMultiImage::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(HotUIMultiImage);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(HotUIImage);

	REFLECTION_CLASSBUILDER_END(HotUIMultiImage);
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(HotUIMultiImageProperties);

void HotUIMultiImageProperties::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(HotUIMultiImageProperties);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(HotUIImageProperties);

		REFLECTION_CLASSBUILDER_FIELD(std::vector<std::string>, ImageList);
	REFLECTION_CLASSBUILDER_END(HotUIMultiImageProperties);
}
