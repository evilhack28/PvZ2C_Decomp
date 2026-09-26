//
//  HotUIComponent.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "HotUIComponent.h"

HotUIComponent::HotUIComponent()
{
}

HotUIComponent::~HotUIComponent()
{
}

HotUIComponentProperties::~HotUIComponentProperties()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(HotUIComponent);

void HotUIComponent::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(HotUIComponent);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(RtObject);

	REFLECTION_CLASSBUILDER_END(HotUIComponent);
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(HotUIComponentProperties);

void HotUIComponentProperties::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(HotUIComponentProperties);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PropertySheetBase);

	REFLECTION_CLASSBUILDER_FIELD(std::vector<RtId>, Targets);

	REFLECTION_CLASSBUILDER_END(HotUIComponentProperties);
}

void HotUIComponent::Update()
{
}

const std::vector<HotUIWidgetPtr>& HotUIComponent::getTargets() const
{
	return m_targets;
}
