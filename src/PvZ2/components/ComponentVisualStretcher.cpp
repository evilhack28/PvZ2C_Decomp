//
//  ComponentVisualStretcher.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "ComponentVisualStretcher.h"

ComponentVisualStretcher::ComponentVisualStretcher()
{
}

ComponentVisualStretcherProps::~ComponentVisualStretcherProps()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ComponentVisualStretcher);

void ComponentVisualStretcher::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ComponentVisualStretcher);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ComponentBase);

		REFLECTION_CLASSBUILDER_FIELD(ComponentVisualStretcherProps, m_props);
		REFLECTION_CLASSBUILDER_FIELD(bool, m_isStretching);
	REFLECTION_CLASSBUILDER_END(ComponentVisualStretcher);
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ComponentVisualStretcherProps);

void ComponentVisualStretcherProps::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ComponentVisualStretcherProps);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PropertySheetBase);

		REFLECTION_CLASSBUILDER_FIELD(float, StretchSpeed);
	REFLECTION_CLASSBUILDER_END(ComponentVisualStretcherProps);
}
