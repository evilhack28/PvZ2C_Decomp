//
//  HotUIAdaptor.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "HotUIAdaptor.h"

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(HotUIAdaptor);

void HotUIAdaptor::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(HotUIAdaptor);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(Sexy::Widget);

	REFLECTION_CLASSBUILDER_END(HotUIAdaptor);
}

#include "HotUIAdaptor.h"
void HotUIAdaptor::LoadWidget()
{
	 HotUIAdaptor::loadUIView();
}

void HotUIAdaptor::ButtonPress(int i_buttonID)
{
}

void HotUIAdaptor::onLoadUIView()
{
}

void HotUIAdaptor::ButtonDepress(int i_buttonID)
{
}

void HotUIAdaptor::SliderReleased(int i_sliderID, double i_value)
{
}

void HotUIAdaptor::onLayoutFinished()
{
}

bool HotUIAdaptor::OnBackButtonPressed()
{
	return false;
}

void HotUIAdaptor::onLinkToUIViewCreated()
{
}

void HotUIAdaptor::SliderVal(int i_sliderID, double i_value)
{
}
