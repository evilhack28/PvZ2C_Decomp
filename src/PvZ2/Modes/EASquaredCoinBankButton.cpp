//
//  EASquaredCoinBankButton.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "EASquaredCoinBankButton.h"

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(EASquaredCoinBankButton);

void EASquaredCoinBankButton::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(EASquaredCoinBankButton);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(SlidingWidget);

	REFLECTION_CLASSBUILDER_END(EASquaredCoinBankButton);
}
