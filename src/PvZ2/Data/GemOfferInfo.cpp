//
//  GemOfferInfo.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-11-21.
//

#include "SexyAppFramework/Common.h"

#include "GemOfferMgr.h"

/////////////// Lifecycle ///////////////

GemOfferInfo::GemOfferInfo()
{
}

GemOfferInfo::~GemOfferInfo()
{
}

/////////////// Reflection ///////////////

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(GemOfferInfo);

void GemOfferInfo::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(GemOfferInfo);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(Sexy::RtObject);

	REFLECTION_CLASSBUILDER_END(GemOfferInfo);
}
