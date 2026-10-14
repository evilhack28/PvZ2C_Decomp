//
//  AdaptorRiftLevelSetup.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "AdaptorRiftLevelSetup.h"

void AdaptorRiftLevelSetup::onLayoutFinished()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(AdaptorRiftLevelSetup);

void AdaptorRiftLevelSetup::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(AdaptorRiftLevelSetup);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(HotUIAdaptor);

	REFLECTION_CLASSBUILDER_END(AdaptorRiftLevelSetup);
}

#include "HotUIAdaptor.h"
void AdaptorRiftLevelSetup::closeDialog()
{
	 HotUIAdaptor::RemoveAndDeleteWidget();
}

#include "AdaptorRiftLevelSetup.h"
void AdaptorRiftLevelSetup::onSuccessResponse()
{
	 AdaptorRiftLevelSetup::startLevel();
}
