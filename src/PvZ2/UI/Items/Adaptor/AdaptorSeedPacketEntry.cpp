//
//  AdaptorSeedPacketEntry.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-11-19.
//

#include "SexyAppFramework/Common.h"

#include "NewPlantUI.h"
#include "HotUIAdaptor.h"
#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(AdaptorSeedPacketEntry);

void AdaptorSeedPacketEntry::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(AdaptorSeedPacketEntry);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(HotUIAdaptor);

	REFLECTION_CLASSBUILDER_END(AdaptorSeedPacketEntry);
}

void AdaptorSeedPacketEntry::onLayoutFinished()
{
	HotUIAdaptor::GetEntryPointWidget();
}
