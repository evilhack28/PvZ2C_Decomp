//
//  AdaptorRiftPerkProgressScreen.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "AdaptorRiftPerkProgressScreen.h"

void AdaptorRiftPerkProgressScreen::refresh()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(AdaptorRiftPerkProgressScreen);

void AdaptorRiftPerkProgressScreen::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(AdaptorRiftPerkProgressScreen);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(HotUIAdaptor);

	REFLECTION_CLASSBUILDER_END(AdaptorRiftPerkProgressScreen);
}

#include "AdaptorRiftPerkProgressScreen.h"
void AdaptorRiftPerkProgressScreen::onLinkToUIViewCreated()
{
	 AdaptorRiftPerkProgressScreen::setup();
}

#include "HotUIAdaptor.h"
void AdaptorRiftPerkProgressScreen::Update()
{
	 HotUIAdaptor::Update();
}
