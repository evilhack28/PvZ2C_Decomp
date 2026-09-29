//
//  HotUIImageBorder.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "HotUIImageBorder.h"

HotUIImageBorderProperties::~HotUIImageBorderProperties()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(HotUIImageBorder);

void HotUIImageBorder::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(HotUIImageBorder);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(HotUIImage);

	REFLECTION_CLASSBUILDER_END(HotUIImageBorder);
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(HotUIImageBorderProperties);

void HotUIImageBorderProperties::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(HotUIImageBorderProperties);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(HotUIImageProperties);

		REFLECTION_CLASSBUILDER_FIELD(UIImageType, BorderDrawType);
		REFLECTION_CLASSBUILDER_FIELD(UIImageDrawStyle, BorderDrawStyle);
		REFLECTION_CLASSBUILDER_FIELD(std::string, BorderImage);
		REFLECTION_CLASSBUILDER_FIELD(DynamicPadding, BorderInsets);
	REFLECTION_CLASSBUILDER_END(HotUIImageBorderProperties);
}
