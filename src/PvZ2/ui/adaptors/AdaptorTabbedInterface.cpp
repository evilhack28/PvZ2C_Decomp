//
//  AdaptorTabbedInterface.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "AdaptorTabbedInterface.h"

AdaptorTabbedInterface::AdaptorTabbedInterface()
{
}

AdaptorTabbedInterface::~AdaptorTabbedInterface()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(AdaptorTabbedInterface);

void AdaptorTabbedInterface::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(AdaptorTabbedInterface);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(HotUIAdaptor);

	REFLECTION_CLASSBUILDER_END(AdaptorTabbedInterface);
}

#include "AdaptorTabbedInterface.h"
void AdaptorTabbedInterface::onLinkToUIViewCreated()
{
	 AdaptorTabbedInterface::setup();
}
