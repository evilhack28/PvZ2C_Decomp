//
//  HotUIPurchaseButton.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "HotUIPurchaseButton.h"

HotUIPurchaseButton::HotUIPurchaseButton()
{
}

HotUIPurchaseButton::~HotUIPurchaseButton()
{
}

HotUIPurchaseButtonProperties::~HotUIPurchaseButtonProperties()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(HotUIPurchaseButton);

void HotUIPurchaseButton::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(HotUIPurchaseButton);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(HotUIButton);

	REFLECTION_CLASSBUILDER_END(HotUIPurchaseButton);
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(HotUIPurchaseButtonProperties);

void HotUIPurchaseButtonProperties::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(HotUIPurchaseButtonProperties);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(HotUIButtonProperties);

	REFLECTION_CLASSBUILDER_FIELD(std::string, CostLabel);

	REFLECTION_CLASSBUILDER_END(HotUIPurchaseButtonProperties);
}
