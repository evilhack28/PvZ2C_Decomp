//
//  HotUIWidget.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "HotUIWidget.h"

HotUIWidgetProperties::~HotUIWidgetProperties()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(HotUIWidget);

void HotUIWidget::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(HotUIWidget);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(Widget);

		REFLECTION_CLASSBUILDER_FIELD(RtWeakPtr<HotUIWidgetProperties>, m_propertySheetPtr);
		REFLECTION_CLASSBUILDER_FIELD(AnchorDescriptor, m_anchorDescriptor);
		REFLECTION_CLASSBUILDER_FIELD(std::vector<RtWeakPtr<HotUIWidget>>, m_anchorChildren);
		REFLECTION_CLASSBUILDER_FIELD(std::vector<std::string>, m_resourceGroups);
		REFLECTION_CLASSBUILDER_FIELD(float, m_darkenBackgroundPct);
	REFLECTION_CLASSBUILDER_END(HotUIWidget);
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(HotUIWidgetProperties);

void HotUIWidget::OnTouchBegan(const Sexy::Touch& i_arg)
{
}

void HotUIWidget::onLayoutFinalized()
{
}

void HotUIWidget::onInitializeWidget()
{
}

void HotUIWidget::onProcessStringReplaceMap(const HotUIStringMap& i_arg)
{
}

int HotUIWidget::getImageWidthForResizeData()
{
	return false;
}

int HotUIWidget::getImageHeightForResizeData()
{
	return false;
}

void HotUIWidget::onDraw(Sexy::Graphics* i_arg)
{
}

void HotUIWidget::onUpdate()
{
}
