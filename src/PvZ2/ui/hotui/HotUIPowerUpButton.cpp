//
//  HotUIPowerUpButton.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "HotUIPowerUpButton.h"

HotUIPowerUpButtonProperties::~HotUIPowerUpButtonProperties()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(HotUIPowerUpButton);

void HotUIPowerUpButton::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(HotUIPowerUpButton);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(HotUIWidget);

	REFLECTION_CLASSBUILDER_END(HotUIPowerUpButton);
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(HotUIPowerUpButtonProperties);

void HotUIPowerUpButtonProperties::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(HotUIPowerUpButtonProperties);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(HotUIWidgetProperties);

	REFLECTION_CLASSBUILDER_END(HotUIPowerUpButtonProperties);
}

HotUIPowerUpButton::HotUIPowerUpButton()
{
	m_wrappedWidget = 0;
}
