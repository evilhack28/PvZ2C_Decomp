//
//  AdaptorRiftResultsScreen.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "AdaptorRiftResultsScreen.h"

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(AdaptorRiftResultsScreen);

void AdaptorRiftResultsScreen::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(AdaptorRiftResultsScreen);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(HotUIAdaptor);

	REFLECTION_CLASSBUILDER_END(AdaptorRiftResultsScreen);
}

#include "AdaptorRiftResultsScreen.h"
void AdaptorRiftResultsScreen::onLinkToUIViewCreated()
{
	 AdaptorRiftResultsScreen::setup();
}

#include "HotUIAdaptor.h"
void AdaptorRiftResultsScreen::Update()
{
	 HotUIAdaptor::Update();
}
