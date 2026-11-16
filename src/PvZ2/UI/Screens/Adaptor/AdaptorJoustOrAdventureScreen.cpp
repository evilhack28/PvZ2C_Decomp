//
//  AdaptorJoustOrAdventureScreen.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "AdaptorJoustOrAdventureScreen.h"

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(AdaptorJoustOrAdventureScreen);

void AdaptorJoustOrAdventureScreen::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(AdaptorJoustOrAdventureScreen);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(HotUIAdaptor);

	REFLECTION_CLASSBUILDER_END(AdaptorJoustOrAdventureScreen);
}

#include "AdaptorJoustOrAdventureScreen.h"
void AdaptorJoustOrAdventureScreen::onLinkToUIViewCreated()
{
	 AdaptorJoustOrAdventureScreen::setup();
}
