//
//  AdaptorJoustNetworkIssue.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "AdaptorJoustNetworkIssue.h"

AdaptorJoustNetworkIssue::~AdaptorJoustNetworkIssue()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(AdaptorJoustNetworkIssue);

void AdaptorJoustNetworkIssue::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(AdaptorJoustNetworkIssue);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(HotUIAdaptor);

	REFLECTION_CLASSBUILDER_END(AdaptorJoustNetworkIssue);
}
