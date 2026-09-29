//
//  AdaptorRiftZombossLevelSetup.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "AdaptorRiftZombossLevelSetup.h"

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(AdaptorRiftZombossLevelSetup);

void AdaptorRiftZombossLevelSetup::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(AdaptorRiftZombossLevelSetup);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(HotUIAdaptor);

	REFLECTION_CLASSBUILDER_END(AdaptorRiftZombossLevelSetup);
}

#include "HotUIAdaptor.h"
void AdaptorRiftZombossLevelSetup::closeDialog()
{
	 HotUIAdaptor::RemoveAndDeleteWidget();
}
