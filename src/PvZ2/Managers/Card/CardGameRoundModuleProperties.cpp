//
//  CardGameRoundModuleProperties.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-11-05.
//

#include "SexyAppFramework/Common.h"

#include "AnimationMgr.h"
#include "RenderQueue.h"
#include "CardGameRound.h"
#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT_ABSTRACT(CardGameRoundModuleProperties);

/////////////// Lifecycle ///////////////

CardGameRoundModuleProperties::CardGameRoundModuleProperties()
{
}

/////////////// Reflection ///////////////

void CardGameRoundModuleProperties::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(CardGameRoundModuleProperties);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;
	REFLECTION_CLASSBUILDER_END(CardGameRoundModuleProperties);
}
